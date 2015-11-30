/*
 * Copyright 2015 Hippo Seven
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// Created by Hippo on 10/19/2015.
//

#include <stdlib.h>

#include "input_stream.h"
#include "../log.h"
#include "utils.h"

InputStream* createInputStream(JNIEnv* env, jobject is)
{
  jclass streamCls = (*env)->GetObjectClass(env, is);
  jmethodID readMID = (*env)->GetMethodID(env, streamCls, "read", "([BII)I");
  jbyteArray buffer;

  if (readMID == NULL) {
    LOGE(EMSG("Can't get read method id"));
    return NULL;
  }

  buffer = (*env)->NewByteArray(env, BUFFER_SIZE);
  buffer = (*env)->NewGlobalRef(env, buffer);
  if (buffer == NULL) {
    LOGE(EMSG("Can't create buffer"));
    return NULL;
  }

  InputStream* inputStream = (InputStream*) malloc(sizeof(InputStream));
  if (inputStream == NULL) {
    LOGE(EMSG("Out of memory"));
    return NULL;
  }

  inputStream->is = (*env)->NewGlobalRef(env, is);
  inputStream->readMID = readMID;
  inputStream->buffer = buffer;

  return inputStream;
}

void destroyInputStream(JNIEnv* env, InputStream* inputStream)
{
  if (inputStream != NULL) {
    (*env)->DeleteGlobalRef(env, inputStream->is);
    (*env)->DeleteGlobalRef(env, inputStream->buffer);
    free(inputStream);
  }
}

size_t readInputStream(JNIEnv* env, InputStream* inputStream, unsigned char* buffer, int offset, size_t size)
{
  size_t remainSize = size;
  size_t readSize = 0;
  int bufferOffset = offset;
  int len;

  while (remainSize > 0) {
    len = MIN(BUFFER_SIZE, remainSize);

    len = (*env)->CallIntMethod(env, inputStream->is, inputStream->readMID, inputStream->buffer, 0, len);
    if ((*env)->ExceptionCheck(env)) {
      LOGE(EMSG("Catch exception"));
      (*env)->ExceptionClear(env);
      len = -1;
    }

    // end of the stream or catch exception
    if (len < 0) {
      break;
    }

    (*env)->GetByteArrayRegion(env, inputStream->buffer, 0, len, (jbyte *) (buffer + bufferOffset));

    remainSize -= len;
    readSize += len;
    bufferOffset += len;
  }

  return readSize;
}
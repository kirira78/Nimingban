/*
 * Copyright 2017 Hippo Seven
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

package com.hippo.nimingban.widget.nmb

import android.content.Context
import android.util.AttributeSet
import android.view.View
import com.facebook.drawee.backends.pipeline.Fresco
import com.facebook.drawee.view.GenericDraweeView

/*
 * Created by Hippo on 6/9/2017.
 */

class NmbThumb @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null,
    defStyleAttr: Int = 0
) : GenericDraweeView(context, attrs, defStyleAttr) {

  // TODO get image url from api
  fun loadThumb(thumb: String?) =
      load(if (thumb.isNullOrEmpty()) null else "http://img6.nimingban.com/thumb/" + thumb)

  fun load(url: String?) {
    if (url.isNullOrEmpty()) {
      visibility = View.GONE
      return
    } else {
      visibility = View.VISIBLE
    }

    val controller = Fresco.newDraweeControllerBuilder()
        .setOldController(controller)
        .setTapToRetryEnabled(true)
        .setAutoPlayAnimations(true)
        .setUri(url)
        .build()
    setController(controller)
  }
}
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

package com.hippo.nimingban.scene.navigation

import com.hippo.nimingban.activity.NmbActivity
import com.hippo.nimingban.scene.NmbScene

/*
 * Created by Hippo on 6/14/2017.
 */

class NavigationScene : NmbScene<NavigationScene, NavigationUi>() {

  override fun createUi(): NavigationUi {
    return NavigationUi(this, activity as NmbActivity, context!!)
  }
}

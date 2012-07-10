/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkAxesWidgetEventTranslator_h
#define __ctkAxesWidgetEventTranslator_h

// QtTesting inlcudes
#include <pqWidgetEventTranslator.h>

// CTK includes
#include <ctkPimpl.h>
#include "ctkWidgetsExport.h"

class CTK_WIDGETS_EXPORT ctkAxesWidgetEventTranslator :
  public pqWidgetEventTranslator
{
  Q_OBJECT

public:
  ctkAxesWidgetEventTranslator(QObject* parent = 0);

  virtual bool translateEvent(QObject *Object, QEvent *Event, bool &Error);

private:
  ctkAxesWidgetEventTranslator(const ctkAxesWidgetEventTranslator&); // NOT implemented
  ctkAxesWidgetEventTranslator& operator=(const ctkAxesWidgetEventTranslator&); // NOT implemented
};

#endif

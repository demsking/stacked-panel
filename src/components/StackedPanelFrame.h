/**
 * HPX Stacked Panel - A fully stylized StackedWidget implementation
 *
 * Copyright (C) 2019  Sébastien Demanou
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HPXSTACKEDPANEL_COMPONENTS_STACKEDPANELFRAME_H_
#define HPXSTACKEDPANEL_COMPONENTS_STACKEDPANELFRAME_H_

#include <QWidget>

#include "global.h"  // NOLINT(build/include)
#include "StackedPanelWidget.h"

class QVBoxLayout;
class QStackedWidget;

namespace HPX {
  class LIBHPXSTACKEDPANEL_EXPORT StackedPanelFrame: public StackedPanelWidget {
    Q_OBJECT

    public:
      enum class State {
        None,
        Loading,
        Empty,
        Ready
      };

    private:
      QVBoxLayout* _layout = nullptr;
      QStackedWidget* _stackedWidget = nullptr;

    public:
      explicit StackedPanelFrame(QWidget* parent = nullptr);

      void setStateWidget(State, QWidget*);
      QWidget* stateWidget(State) const;
      QWidget* currentWidget() const;
      State currentState() const;

      void setFocus() override;

    public slots:
      void setCurrentState(State);

    protected slots:
      void currentIndexChange(int);

    signals:
      void currentStateChanged(State);
  };
} // namespace HPX

#endif // HPXSTACKEDPANEL_COMPONENTS_STACKEDPANELFRAME_H_

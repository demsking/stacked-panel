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

#ifndef HPXSTACKEDPANEL_COMPONENTS_TABVIEW_H_
#define HPXSTACKEDPANEL_COMPONENTS_TABVIEW_H_

#include <QFrame>

#include "global.h"  // NOLINT(build/include)

class QWidget;
class QVBoxLayout;
class QStackedWidget;

namespace HPX {
  class StackedPanelBar;
  class StackedPanelWidget;
  class StackedPanelModel;

  class LIBHPXSTACKEDPANEL_EXPORT StackedPanel: public QFrame {
    Q_OBJECT

    QVBoxLayout* _mainLayout = nullptr;
    StackedPanelBar* _panelBar = nullptr;
    QStackedWidget* _stackedWidget = nullptr;
    StackedPanelModel* _model = nullptr;
    int _currentIndex = -1;
    bool _freezed = false;

    public:
      explicit StackedPanel(QWidget* parent = nullptr);

      StackedPanelBar* panelBar() const;

      StackedPanelModel* model() const;
      void setModel(StackedPanelModel*);

      StackedPanelWidget* widget(int index) const;
      StackedPanelWidget* currentWidget() const;
      QList<StackedPanelWidget*> widgets() const;

      int indexOf(StackedPanelWidget*);
      int currentIndex() const;

      bool freezed() const;
      void setFreezed(bool freezed);

    public slots:
      void setCurrentIndex(int index);
      void setCurrentWidget(StackedPanelWidget*);

    protected:
      void emitFocusOutWidget(int index);
      void emitFocusIntWidget(int index);

    protected slots:
      void onCurrentIndexChange(int index);
      void onDataInsert(const QModelIndex& parent, int first, int last);
      void onDataAboutRemove(const QModelIndex& parent, int first, int last);
      void onDataRemove(const QModelIndex& parent, int first, int last);
      void onDataChange(const QModelIndex& topLeft,
                        const QModelIndex& bottomRight,
                        const QVector<int>& roles);

    signals:
      void currentIndexChanged(int index);
      void currentWidgetChanged(StackedPanelWidget*);
  };
}  // namespace HPX

#endif // HPXSTACKEDPANEL_COMPONENTS_TABVIEW_H_

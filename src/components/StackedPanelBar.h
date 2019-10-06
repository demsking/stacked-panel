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

#ifndef HPXSTACKEDPANEL_COMPONENTS_TABVIEWBAR_H_
#define HPXSTACKEDPANEL_COMPONENTS_TABVIEWBAR_H_

#include <QList>
#include <QFrame>

#include "global.h"  // NOLINT(build/include)

class QWidget;
class QComboBox;
class QHBoxLayout;
class QStackedWidget;
class QAbstractButton;

namespace HPX {
  class StackedPanelModel;
  class StackedPanelFrame;
  class StackedPanelBarButton;
  class StackedPanelToolbox;

  class LIBHPXSTACKEDPANEL_EXPORT StackedPanelBar: public QFrame {
    Q_OBJECT

    QHBoxLayout* _layout = nullptr;
    QComboBox* _panelCombobox = nullptr;
    QStackedWidget* _stackedToolbox = nullptr;

    StackedPanelToolbox* _globalLeftToolbox = nullptr;
    StackedPanelToolbox* _globalRightToolbox = nullptr;

    StackedPanelModel* _model = nullptr;

    public:
      enum class Position {
        Left,
        Right
      };

    public:
      explicit StackedPanelBar(QWidget* parent = nullptr);

      StackedPanelModel* model() const;
      void setModel(StackedPanelModel*);

      int currentIndex() const;
      QComboBox* widgetComboBox() const;

      void addGlobalWidget(QWidget*, Position, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
      void removeGlobalWidget(QWidget*);

    public slots:
      void setCurrentIndex(int index);

    protected:
      inline void insert(const QModelIndex&, int pos);

    protected slots:
      void updateStackedToolboxSize(int);
      void onRowsInsert(const QModelIndex& parent, int first, int last);
      void onRowsRemove(const QModelIndex& parent, int first, int last);

    signals:
      void currentChanged(int index);
  };
}  // namespace HPX

#endif  // HPXSTACKEDPANEL_COMPONENTS_TABVIEWBAR_H_

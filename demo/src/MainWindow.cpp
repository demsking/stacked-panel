/**
 * HPX Tabview - A fully stylized TabsView implementation
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

#include "MainWindow.h"

#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileSystemWatcher>

#include <QDebug>

#include "components/StackedPanel.h"
#include "components/StackedPanelFrame.h"
#include "components/StackedPanelWidget.h"
#include "components/StackedPanelToolbox.h"
#include "models/StackedPanelModel.h"
#include "models/StackedPanelItem.h"

class PanelWidget: public HPX::StackedPanelWidget {
  QLabel _label;

  public:
    explicit PanelWidget(const QString& label): HPX::StackedPanelWidget(), _label(label) {
      connect(this, &PanelWidget::focusIn, [this]() {
        qDebug() << _label.text() << ":> FOCUS_IN" << isActive();
      });

      connect(this, &PanelWidget::focusOut, [this]() {
        qDebug() << _label.text() << ":> FOCUS_OUT" << isActive();
      });
    }
};

class PanelFrame: public HPX::StackedPanelFrame {
    QLabel _label;

  public:
    explicit PanelFrame(const QString& label): HPX::StackedPanelFrame(), _label(label) {
      setStateWidget(HPX::StackedPanelFrame::State::Ready, &_label);

      connect(this, &PanelWidget::focusIn, [this]() {
        qDebug() << _label.text() << ":> FOCUS_IN" << isActive();
      });

      connect(this, &PanelWidget::focusOut, [this]() {
        qDebug() << _label.text() << ":> FOCUS_OUT" << isActive();
      });
    }
};

MainWindow::MainWindow(const char* theme): QMainWindow() {
  setWindowTitle("HPX Stacked Panel Demo");
  setGeometry(892, 342, 200, 210);

  _panel = new HPX::StackedPanel(this);
  _model = new HPX::StackedPanelModel(this);

  _panel->setModel(_model);
  _panel->setFreezed(true);

  setCentralWidget(_panel);

  for (int i = 0; i < 5; i++) {
    if (i < 2) {
      auto label = QString("Widget %1").arg(i);
      auto widget = new PanelWidget(label);
      auto toolbox = widget->toolbox();
      auto item = new HPX::StackedPanelItem(label, widget);

      if (i) {
        for (int j = 0; j < i; j++) {
          toolbox->addButton(new QPushButton(QString("B%1").arg(j)));
        }
      }

      _model->add(item);
    } else {
      auto label = QString("Panel %1").arg(i);
      auto widget = new PanelFrame(label);
      auto toolbox = widget->toolbox();
      auto item = new HPX::StackedPanelItem(label, widget);

      if (i < 5) {
        widget->setCurrentState(static_cast<HPX::StackedPanelFrame::State>(i));
      }

      if (i) {
        for (int j = 0; j < i; j++) {
          toolbox->addButton(new QPushButton(QString("B%1").arg(j)));
        }
      }

      _model->add(item);
    }
  }

  _panel->setFreezed(false);

  QFileSystemWatcher* themeWatcher = new QFileSystemWatcher({ theme }, this);

  loadTheme(theme);
  connect(themeWatcher, &QFileSystemWatcher::fileChanged, this, &MainWindow::loadTheme);
}

void MainWindow::loadTheme(const QString& filename) {
  QFile stylesheet(filename);
  stylesheet.open(QFile::ReadOnly);

  QString rules = QLatin1String(stylesheet.readAll());
  setStyleSheet(rules);
}

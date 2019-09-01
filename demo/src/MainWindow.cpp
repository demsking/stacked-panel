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
#include "components/StackedPanelBar.h"

#include "components/LandingWidget.h"

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
  setGeometry(892, 342, 250, 610);

  _panel = new HPX::StackedPanel(this);
  _model = new HPX::StackedPanelModel(this);

  _panel->setModel(_model);
  _panel->setFreezed(true);

  _panel->panelBar()->addGlobalButton(new QPushButton("GL"), HPX::StackedPanelBar::Position::Left);
  _panel->panelBar()->addGlobalButton(new QPushButton("GR"), HPX::StackedPanelBar::Position::Right);

  setCentralWidget(_panel);

  const int MAX_WIDGETS = 2;
  const char* LOREM = "Lorem ipsum dolor sit amet, consectetur adipiscing elit";

  for (int i = 0; i < 6; i++) {
    if (i < MAX_WIDGETS) {
      auto label = QString("Widget %1").arg(i);
      auto widget = new PanelWidget(label);
      auto toolbox = widget->toolbox();
      auto item = new HPX::StackedPanelItem(label, widget);

      if (i) {
        for (int j = 0; j < i; j++) {
          toolbox->addButton(new QPushButton(QString("B%1").arg(j)));
        }
      }

      _model->appendRow(item);
    } else {
      auto label = QString("Panel %1").arg(i);
      auto widget = new PanelFrame(label);
      auto toolbox = widget->toolbox();
      auto item = new HPX::StackedPanelItem(label, widget);
      auto state = static_cast<HPX::StackedPanelFrame::State>(i - MAX_WIDGETS);

      if (i < 5) {
        widget->setCurrentState(state);
      }

      switch (state) {
        case HPX::StackedPanelFrame::State::None:
          widget->setStateWidget(state, new HPX::LandingWidget("None", LOREM, this));
          break;

        case HPX::StackedPanelFrame::State::Empty: {
          auto emptyWidget = new HPX::LandingWidget("Empty", LOREM, this);

          emptyWidget->addButton(new QPushButton("New Project"));
          emptyWidget->addButton(new QPushButton("Open Project"));

          widget->setStateWidget(state, emptyWidget);
          break;
        }

        case HPX::StackedPanelFrame::State::Loading:
          widget->setStateWidget(state, new HPX::LandingWidget("Loading", LOREM, this));
          break;

        case HPX::StackedPanelFrame::State::Ready: {
          auto emptyWidget = new HPX::LandingWidget("Ready", LOREM, this);

          emptyWidget->addButton(new QPushButton("Start Coding"));

          widget->setStateWidget(state, emptyWidget);
          break;
        }
      }

      if (i) {
        for (int j = 0; j < i; j++) {
          toolbox->addButton(new QPushButton(QString("B%1").arg(j)));
        }
      }

      _model->appendRow(item);
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

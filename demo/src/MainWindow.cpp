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

#include <exception>

#include <QFile>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileSystemWatcher>

#include "../../src/components/StackedPanel.h"
#include "../../src/components/StackedPanelWidget.h"
#include "../../src/components/StackedPanelToolbox.h"
#include "../../src/models/StackedPanelModel.h"
#include "../../src/models/StackedPanelItem.h"

class Widget: public HPX::StackedPanelWidget {
  QLabel _label;

  public:
    explicit Widget(const QString& label): _label(label, this) {}
};

MainWindow::MainWindow(const char* theme): QMainWindow() {
  setWindowTitle("HPX Stacked Panel Demo");
  setGeometry(892, 342, 200, 650);

  _panel = new HPX::StackedPanel(this);
  _model = new HPX::StackedPanelModel(this);

  _panel->setModel(_model);

  setCentralWidget(_panel);

  try {
    auto item = new HPX::StackedPanelItem();

    item->setName("exception");
    _model->add(item);
  } catch (std::exception e) {
    _model->removeRow(0);
  }

  for (int i = 0; i < 5; i++) {
    const QString label = QString("Item %1").arg(i);
    HPX::StackedPanelToolbox* toolbox = new HPX::StackedPanelToolbox();
    HPX::StackedPanelItem* item = new HPX::StackedPanelItem();

    item->setName(label);
    item->setWidget(new Widget(label));

    if (i) {
      for (int j = 0; j < i; j++) {
        toolbox->addButton(new QPushButton(QString("B%1").arg(j)));
      }

      item->setToolbox(toolbox);
    }

    _model->add(item);
  }

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

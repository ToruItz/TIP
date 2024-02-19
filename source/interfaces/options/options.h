/*
    "Text Insertion Program (TIP)" is a software
    for client management and generating unique images for each client.
    Copyright (C) 2024  Pavel Remdenok

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

// Qt
#include <QDialog>

// Services
#include <services/settings/settings_manager.h>

namespace Ui {
    class Options;
}

class Options : public QDialog {
Q_OBJECT

public:
    explicit Options(QWidget *parent = nullptr);

    ~Options() override;

private slots:

    void on_path_to_button_clicked();

    void on_path_to_edit_textChanged(const QString &text);

    void on_theme_combo_box_currentIndexChanged(int);

    void on_change_button_ex_1_clicked();

    void on_change_button_ex_2_clicked();

    void on_change_button_ex_3_clicked();

    void on_change_text_position_button_clicked();

    void on_database_edit_button_clicked();

    void on_save_button_clicked();

    void on_image_url_edit_textChanged(const QString &text);

    void on_image_format_edit_textChanged(const QString &text);

    void on_advanced_settings_button_clicked();

private:

    void SetAdvancedSettingsVisible(bool state);

    SettingsManager settings_manager_;
    int save_type_ = SettingsManager::SaveType::SAVE_NONE;

    SettingsManager::Settings settings_buffer_;

    Ui::Options *ui;
};

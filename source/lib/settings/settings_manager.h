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

// STDLIB
#include <array>
#include <cstddef>

// Qt
#include <QColor>
#include <QFont>
#include <QImage>
#include <QPointF>
#include <QString>

// Local
#include "const_options.h"
#include "ini-parser/inicpp.h"

// Services
#include "database.h"
#include "models.h"

class SettingsManager {
public:
    enum SaveType {
        SAVE_NONE = 0b000,
        SAVE_DATABASE = 0b001,
        SAVE_SYNCING = 0b010,
        SAVE_GENERAL = 0b100,
        SAVE_LOCAL = SAVE_DATABASE | SAVE_GENERAL,
        SAVE_ALL = SAVE_LOCAL | SAVE_SYNCING
    };

    struct Settings {
        const Constants consts;
        QString output_folder;
        QString theme;
        std::array<Models::FontSettings, 3> font_settings;
        Models::Database database;
        QImage image;
        Models::Passwords passwords;

        Settings& operator=(const Settings& other) {
            output_folder = other.output_folder;
            theme = other.theme;
            font_settings = other.font_settings;
            database = other.database;
            image = other.image;
            passwords = other.passwords;
            return *this;
        }
    };

    explicit SettingsManager(const QString& connection_name = "default");

    void ReloadSettings();

    Settings GetSettings();

    void SetSettings(const Settings& settings);

    void Save(int type = SaveType::SAVE_ALL);

private:
    void LoadFromDatabase();

    void LoadFromIni(const QString& connection_name);

    Database database_;

    Settings settings_;
    ini::IniFile settings_file_;

    const QString SELECT_FONT_SETTINGS = "SELECT * FROM %1.font_settings;";

    const QString UPDATE_FONT_SETTINGS =
        "UPDATE %1.font_settings SET font = %2, color = %3, position_x = %4, position_y = %5, size = %6, bold = %7 WHERE id = %8;";

    const QString SELECT_IMAGE = "SELECT base64 FROM %1.image WHERE id = 1;";

    const QString UPDATE_IMAGE = "UPDATE %1.image SET base64 = :img WHERE id = 1;";

    const QString SELECT_PASSWORDS = "SELECT * FROM %1.advanced_settings_passwords;";

    const std::string SETTINGS_FILE_PATH_ = "./settings/settings.ini";

    const std::string DEFAULT_SETTINGS_ = {
        "[general]\n"
        "path_to=default\n"
        "theme=Darkeum\n\n"
        "[database]\n"
        "host=localhost\n"
        "port=5432\n"
        "username=postgres\n"
        "password=root\n"
        "name=tip\n"
        "schema=main\n"
    };
};

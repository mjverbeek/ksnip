/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "PlatformChecker.h"

PlatformChecker* PlatformChecker::instance()
{
    static PlatformChecker instance;
    return &instance;
}

PlatformChecker::Platform PlatformChecker::platform() const
{
    return mPlatform;
}

PlatformChecker::Environment PlatformChecker::environment() const
{
    return mEnvironment;
}

void PlatformChecker::checkPlatform()
{
    CommandRunner runner;
    auto output = runner.getEnviromentVariable("XDG_SESSION_TYPE");
    if (outputContainsValue(output, "x11")) {
        qCritical("Platform: X11");
        mPlatform = Platform::X11;
    } else if (outputContainsValue(output, "wayland")) {
        qCritical("Platform: Wayland");
        mPlatform = Platform::Wayland;
    } else {
        qCritical("Platform: Unknown");
        mPlatform = Platform::Unknown;
    }
}

void PlatformChecker::checkEnvironment()
{
    CommandRunner runner;
    auto output = runner.getEnviromentVariable("XDG_CURRENT_DESKTOP");
    if (outputContainsValue(output, "kde")) {
        qCritical("Window Manager: KDE");
        mEnvironment = Environment::KDE;
    } else if (outputContainsValue(output, "gnome")) {
        qCritical("Window Manager: Gnome");
        mEnvironment = Environment::KDE;
    } else {
        qCritical("Window Manager: Unknown");
        mEnvironment = Environment::Unknown;
    }
}

bool PlatformChecker::outputContainsValue(const QString& output, const QString& value) const
{
    return output.contains(value.toLatin1(), Qt::CaseInsensitive);
}

PlatformChecker::PlatformChecker()
{
    checkPlatform();
    checkEnvironment();
}
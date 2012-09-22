/* ***** BEGIN LICENSE BLOCK *****
*   Copyright (C) 2012, Peter Hatina <phatina@gmail.com>
*
*   This program is free software; you can redistribute it and/or
*   modify it under the terms of the GNU General Public License as
*   published by the Free Software Foundation; either version 2 of
*   the License, or (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program. If not, see <http://www.gnu.org/licenses/>.
* ***** END LICENSE BLOCK ***** */

#include <config.h>
#include <algorithm>
#include "simple-mtpfs-tmp-files-pool.h"
#include "simple-mtpfs-sha1.h"

TmpFilesPool::TmpFilesPool():
    m_tmp_path("/tmp/simple-mtpfs"),
    m_pool()
{
}

TmpFilesPool::~TmpFilesPool()
{
}

void TmpFilesPool::addFile(const TypeTmpFile &tmp)
{
    m_pool.insert(tmp);
}

void TmpFilesPool::removeFile(const std::string &tmp_file)
{
    auto it = std::find(m_pool.begin(), m_pool.end(), tmp_file);
    if (it == m_pool.end())
        return;
    m_pool.erase(it);
}

const TypeTmpFile *TmpFilesPool::getFile(const std::string &path) const
{
    std::string tmp_path = makeTmpPath(path);
    auto it = std::find(m_pool.begin(), m_pool.end(), tmp_path);
    if (it == m_pool.end())
        return nullptr;
    return static_cast<const TypeTmpFile*>(&*it);
}

std::string TmpFilesPool::makeTmpPath(const std::string &path_device) const
{
    return m_tmp_path + std::string("/") + SHA1::sumString(path_device);
}

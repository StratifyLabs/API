// Copyright 2011-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef FSAPI_FILE_HPP_
#define FSAPI_FILE_HPP_

namespace fs {}

#if !defined __link
#include "fs/Aio.hpp"
#else
#include "fs/AssetFileSystem.hpp"
#endif

#include "fs/DataFile.hpp"
#include "fs/Dir.hpp"
#include "fs/File.hpp"
#include "fs/FileInfo.hpp"
#include "fs/FileSystem.hpp"
#include "fs/LambdaFile.hpp"
#include "fs/Path.hpp"
#include "fs/ViewFile.hpp"

using namespace fs;

#endif /* FSAPI_FILE_HPP_ */

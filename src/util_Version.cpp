/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/util_Version.cpp -- Version class implementation.
 */

#include <elm/util/Version.h>

namespace elm {


/**
 * @class Version
 * Useful for representing versions. The versions are represented as a triplet
 * composed of a major number, a minor number and a release number. Different
 * major numbers means that two versions are uncompatible. The minor version
 * number means ascending compatibility. The release number versions only
 * denotes different debugging versions (no change in the interface of a
 * compilation unit).
 */


/**
 * @fn Version::Version(int major, int minor = 0, int release = 0);
 * Build a new version.
 * @param major		Major number.
 * @param minor		Minor number.
 * @param release	Release number.
 */


/**
 * @fn Version::Version(const Version& version);
 * Build a version by cloning.
 * @param version	Cloned version.
 */


/**
 * @fn Version Version::nextRelease(void) const;
 * Build a version with the next release.
 */


/**
 * @fn Version Version::nextMinor(void) const;
 * Build a version with the next minor number.
 */


/**
 * @fn Version Version::nextMajor(void) const;
 * Build a version with the next major number.
 */


/**
 * @fn int Version::major(void) const;
 * Get the major number.
 */


/**
 * @fn int Version::minor(void) const;
 * Get the minor number.
 */


/**
 * @fn int Version::release(void) const;
 * Get the release number.
 */


/**
 * @fn bool Version::accepts(const Version& version) const;
 * Test if the current version accepts the given one, that is, the current one
 * is ascendent-compatible with the given one.
 * @param version	Version to compare with.
 */


/**
 * @fn int Version::compare(const Version& version) const;
 * Compare two versions. Notice that comparison is only performed on major and
 * minor numbers.
 * @param version	Version to compare with.
 * @return			0 for equality, <0 if current is less than passed one,
 * 					>0 else.
 */


/**
 * Zero version, that is, 0.0.0.
 */
const Version Version::ZERO;

}; // elm

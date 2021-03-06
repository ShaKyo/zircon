// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <fuzz-utils/string-map.h>
#include <stdint.h>

#include "fixture.h"

namespace fuzzing {
namespace testing {

// |fuzzing::testing::FuzzerFixture| is a fixture that understands fuzzer path locations.  It should
// not be instantiated directly; use |CreateZircon| or |CreateFuchsia| below.
class FuzzerFixture final : public Fixture {
public:
    // Indicates a package should include the fuzz target binary.
    static constexpr uint8_t kHasBinary = 0x01;
    // Indicates a package should include immutable fuzzing resources like seed corpus locations,
    // dictionaries, and option files.
    static constexpr uint8_t kHasResources = 0x02;
    // Indicates a package should include mutable fuzzing data like a corpus and artifacts from
    // previous executions.
    static constexpr uint8_t kHasData = 0x04;

    // Creates a number of temporary, fake directories and files to mimic a deployment of
    // fuzz-targets on Zircon.  The files and directories are automatically deleted when the fixture
    // is destroyed.
    bool CreateZircon();

    // Creates a number of temporary, fake directories and files to mimic a deployment of
    // fuzz-packages on Fuchsia. The files and directories are automatically deleted when the
    // fixture is destroyed.
    bool CreateFuchsia();

    // Returns the maximum version of the given |Package| in the fixture as a C-style string, or
    // null if the package wasn't created by the fixture.
    const char* max_version(const char* package) const { return max_versions_.get(package); }

protected:
    // Resets the object to a pristine state.
    void Reset() override;

private:
    // Creates a fake fuzz |target| in the given |version| of a fake Fuchsia |package|. Adds fake
    // executable and data files as indicated by |flags|.
    bool CreatePackage(const char* package, long int version, const char* target, uint8_t flags);

    // maps packages to maximum versions.
    StringMap max_versions_;
};

} // namespace testing
} // namespace fuzzing

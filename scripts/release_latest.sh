#!/usr/bin/env bash

scripts/release.sh "$(scripts/repo_name.sh)" "$(git describe)" -- \
  "./builds/macOS/Release/Strategr.$(git describe).dmg" \
  "./builds/macOS/Release/Strategr.macOS.$(git describe).zip"
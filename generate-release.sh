#!/bin/bash

increment_version() {
    local version=$1
    local major minor patch

    # Split version into components
    IFS='.' read -r major minor patch <<< "$version"

    # Increment patch version
    patch=$((patch + 1))

    echo "$major.$minor.$patch"
}

current_version=$(head -n 1 version)

new_version=$(increment_version "$current_version")

echo "$new_version" > version

sed -i.bak "s/$current_version/$new_version/" README.md && rm README.md.bak

sed -i.bak "s/$current_version/$new_version/" src/main.cpp && rm src/main.cpp.bak

git add platformio.ini README.md src/main.cpp
git commit -m "Bump version to v$new_version"

git tag -a "v$new_version" -m v"Version $new_version"

git push origin main
git push origin "v$new_version"

echo "Create a new release on GitHub:"
echo "https://github.com/serginator/cardputer-mouse-jiggler/releases/new?tag=v$new_version"

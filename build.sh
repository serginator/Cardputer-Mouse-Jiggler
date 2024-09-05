#!/bin/bash

# Function to increment version
increment_version() {
    local version=$1
    local major minor patch

    # Split version into components
    IFS='.' read -r major minor patch <<< "$version"

    # Increment patch version
    patch=$((patch + 1))

    echo "$major.$minor.$patch"
}

# Get current version from platformio.ini
current_version=$(grep 'version =' platformio.ini | sed 's/version = //')

# Increment version
new_version=$(increment_version "$current_version")

# Update version in platformio.ini
sed -i.bak "s/version = $current_version/version = $new_version/" platformio.ini && rm platformio.ini.bak

# Update version in README.md
sed -i.bak "s/$current_version/$new_version/" README.md && rm README.md.bak

# Update version in src/main.cpp
sed -i.bak "s/$current_version/$new_version/" src/main.cpp && rm src/main.cpp.bak

# Commit changes
git add platformio.ini README.md src/main.cpp
git commit -m "Bump version to v$new_version"

# Create annotated tag
git tag -a "v$new_version" -m v"Version $new_version"

# Push changes and tag
git push origin main
git push origin "v$new_version"

# Print GitHub release URL
echo "Create a new release on GitHub:"
echo "https://github.com/yourusername/your-repo-name/releases/new?tag=v$new_version"

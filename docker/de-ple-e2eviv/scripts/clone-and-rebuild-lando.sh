#! /bin/bash
set -e # exit immediately upon error(s)

# Obtain parent directory of script folder.
ROOT_DIR=$(dirname -- "$(dirname -- "$(readlink -f -- "$0")")")

# Git URL and version of the Lando tool distribution
LANDO_REPO_URL="https://github.com/GaloisInc/BESSPIN-Lando.git"
LANDO_VERSION=db552ec74d4532611280693438207a72a23045b4

# ANSI escape sequences for colorful terminal output
ANSI_RESET='\033[0m'
ANSI_BOLD='\033[1m'

# Print an informative message for the next step.
function section {
  echo -e "${ANSI_BOLD}$1${ANSI_RESET}"
}

# Function to clone the SSITH lando GitLab repository.
function clone_lando {
  section "Cloning lando repository and checking out release commit ..."
  rm -rf lando
  git clone --branch develop --single-branch "$LANDO_REPO_URL" lando
  pushd lando > /dev/null
  git reset --hard $LANDO_VERSION
  popd > /dev/null
}

# Function to rebuild lando, resulting in a fresh jar.
function rebuild_lando {
  section "Rebuilding lando JAR from sources ..."
  pushd lando/source/lando > /dev/null
  mvn clean package
  popd > /dev/null
}

# Function to deploy the lando JAR into the resources/lando/lib folder.
function deploy_lando {
  section "Deploying lando JAR to docker resources folder ..."
  pushd lando/source/lando > /dev/null
  LANDO_JAR=`find . -name 'lando-*-jar-with-dependencies.jar' -type f`
  echo "Copying $LANDO_JAR to $ROOT_DIR/resources/"
  rm -rf "$ROOT_DIR/resources/lando/lib"
  mkdir -p "$ROOT_DIR/resources/lando/lib"
  cp "$LANDO_JAR" "$ROOT_DIR/resources/lando/lib"
  popd > /dev/null
}

# Main behavior of the script
mkdir -p "$ROOT_DIR/repository"
pushd "$ROOT_DIR/repository" > /dev/null
clone_lando
rebuild_lando
deploy_lando
popd > /dev/null

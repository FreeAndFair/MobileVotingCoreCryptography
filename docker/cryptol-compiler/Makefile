################################################################################
# Makefile to build and deploy the Free & Fair Cryptol Compiler Docker image   #
################################################################################
# Possible commands are:
# make [default|all|help|login|logout|clone|image|save|pull|push|remove|clean]

# URL of the Docker repository to push the image to
DOCKER_REPOSITORY := registry-1.docker.io

# Organization within the Docker repository to push to
DOCKER_ORGANIZATION := freeandfair

# Name of the Docker image to be created
IMAGE = cryptol-compiler

# Platforms to build the docker image (multi-platform build)
IMAGE_PLATFORMS = linux/amd64,linux/arm64/v8

# For testing multi-platform builds
IMAGE_PLATFORMS = linux/amd64,linux/arm64/v8
IMAGE_PLATFORM1 = linux/amd64
IMAGE_PLATFORM2 = linux/arm64

# Docker-compatible command to use.  A standard alternative is `podman`.
# Override via an environment variable (e.g., "make DOCKER=podman ...").
DOCKER ?= docker

# Detect whether we are using docker or podman, as they appear to have
# different command line options and thus might need special treatment.
DOCKER_VERSION   := $(shell $(DOCKER) --version)
DOCKER_OR_PODMAN := $(firstword $(DOCKER_VERSION))

# For Podman, we do not use Docker-specific attestation or SBOM options
ifeq ($(DOCKER_OR_PODMAN), podman)
DOCKER_BUILD_ARGS =
else
DOCKER_BUILD_ARGS = --attest type=provenance,mode=max --attest type=sbom
endif

# URL of the cryptol-compiler repository (on Galois GitLab)
CRYPTOL_COMPILER_GIT = git@gitlab-ext.galois.com:grindstone/cryptol-compiler.git

# Git tag of the cryptol-compiler release to be installed
CRYPTOL_COMPILER_TAG = 0.9.0.0

# ANSI escape sequences for colored terminal output
ANSI_NORM    := \033[0m
ANSI_BOLD    := \033[1m
ANSI_BLACK   := \033[0;30m
ANSI_RED     := \033[0;31m
ANSI_GREEN   := \033[0;32m
ANSI_YELLOW  := \033[0;33m
ANSI_BLUE    := \033[0;34m
ANSI_MAGENTA := \033[0;35m
ANSI_CYAN    := \033[0;36m
ANSI_WHITE   := \033[0;37m

# The default target displays the help page.
default: help

# Clone and build cryptol-compiler and create Docker image.
all: clone image

# Display a brief help page listing possible commands/targets.
help:
	@echo "Possible commands/targets are:"
	@echo "make all      - clone cryptol-compiler and create Docker image"
	@echo "make login    - log user into DockerHub repository"
	@echo "make logout   - log user out of DockerHub repository"
	@echo "make clone    - freshly clone and prepare cryptol-compiler;"
	@echo "                requires access to the respecitive repository"
	@echo "make image    - create $(IMAGE) Docker image (in local store)"
	@echo "make save     - save $(IMAGE) Docker image to a tar file"
	@echo "make pull     - pull $(IMAGE) Docker image from DockerHub repository"
	@echo "make push     - push $(IMAGE) Docker image to DockerHub repository"
	@echo "make remove   - remove $(IMAGE) Docker image from local store"
	@echo "make clean    - remove all dynamically created files, incl. repository clone"
	@echo "make help     - display this help page (default target)"

# Log into DockerHub Docker repository.
login:
	$(info [info] logging into DockerHub repository)
	$(DOCKER) login $(DOCKER_REPOSITORY)

# Log out of DockerHub Docker repository.
logout:
	$(info [info] Logging out of DockerHub repository)
	$(DOCKER) logout $(DOCKER_REPOSITORY)

# Clone cryptol-compiler repository into 'repositories' folder.
clone:
	$(info [info] Cloning and prepping the cryptol-compiler repository ...)
	@echo "[$(ANSI_RED)note$(ANSI_NORM)] Requires access to the $(ANSI_BOLD)$(CRYPTOL_COMPILER_GIT)$(ANSI_NORM) repository on Galois GitLab."
	@cd repositories && rm -rf cryptol-compiler && git clone -c advice.detachedHead=false -b $(CRYPTOL_COMPILER_TAG) $(CRYPTOL_COMPILER_GIT) cryptol-compiler
	@cd repositories/cryptol-compiler && git submodule update --init --recursive

# Create multi-platform Docker image
image:
	$(info [info] rebuilding $(IMAGE) Docker image ...)
	$(DOCKER) buildx build --platform $(IMAGE_PLATFORMS) --build-arg CRYPTOL_COMPILER_TAG=$(CRYPTOL_COMPILER_TAG) -t $(IMAGE):$(CRYPTOL_COMPILER_TAG) $(DOCKER_BUILD_ARGS) .

# Save Docker image locally to a .tar file.
save:
	$(info [info] saving Docker image to $(IMAGE).tar ...)
	$(DOCKER) save -o $(IMAGE).tar $(IMAGE)

# Pull Docker image from DockerHub private repository.
pull: login
	$(DOCKER) pull $(DOCKER_ORGANIZATION)/$(IMAGE):$(CRYPTOL_COMPILER_TAG)

# Push Docker image to DockerHub private repository.
# @review Shall we tag and push as $(DOCKER_ORGANIZATION)/$(IMAGE):latest?
push: login
	$(DOCKER) image tag $(IMAGE):$(CRYPTOL_COMPILER_TAG) $(DOCKER_ORGANIZATION)/$(IMAGE):$(CRYPTOL_COMPILER_TAG)
	$(DOCKER) image tag $(IMAGE):$(CRYPTOL_COMPILER_TAG) $(DOCKER_ORGANIZATION)/$(IMAGE):latest
	$(DOCKER) push $(DOCKER_ORGANIZATION)/$(IMAGE):$(CRYPTOL_COMPILER_TAG)
	$(DOCKER) push $(DOCKER_ORGANIZATION)/$(IMAGE):latest

# Push Docker image from local image cache / store.
remove:
	$(info [info] removing $(IMAGE) image locally ...)
	$(DOCKER) rmi $(IMAGE)

# Clean up all dynamically generated files, including lando clone.
clean:
	$(info [info] cleaning up all dynamically generated files ...)
	rm -rf repositories/cryptol-compiler
	rm -f $(IMAGE).tar

PHONY: default all help login logout clone image save pull push remove clean

###############################################################################
# Makefile to build and deploy the Free&Fair DE/PLE Docker image, © Free&Fair #
###############################################################################
# Possible commands are: make [all|lando|image|save|remove|clean]

# URL for the Docker repository to push the image to.
DOCKER_REPOSITORY := registry-1.docker.io

# Organization within the Docker repository to push to.
DOCKER_ORGANIZATON := freeandfair

# Name of the Docker image to be created.
IMAGE=de-ple-e2eviv

# Docker-compatible command to use.  A standard alternative is `podman`.
# Override via an environment variable (e.g., "make DOCKER=podman ...").
DOCKER=docker

# Different command line options for Podman, in the event that we
# need them. This was inspired by trying to fix a build problem, and
# even though it doesn't do anything right now it might in the future.

DOCKER_VERSION := $(shell $(DOCKER) --version)
DOCKER_OR_PODMAN := $(firstword $(DOCKER_VERSION))

DOCKER_BUILD_ARGS=--platform="linux/amd64"
ifeq ($(DOCKER_OR_PODMAN), podman)
# modify build arguments for Podman here
endif

# Default target: help
all: help

# Display a brief help page listing possible commands/targets.
help:
	@echo "Possible commands/targets are:"
	@echo "make [all]  - clone and rebuild Lando and create $(IMAGE) image"
	@echo "make login  - log user into DockerHub repository"
	@echo "make logout - log user out of DockerHub repository"
	@echo "make lando  - clone and rebuild Lando (prerequisite for building)"
	@echo "make image  - create $(IMAGE) image (in local store)"
	@echo "make save   - save $(IMAGE) image to a tar file"
	@echo "make pull   - pull de-ple-e2eviv image from DockerHub repository"
	@echo "make push   - push de-ple-e2eviv image to DockerHub repository"
	@echo "make remove - remove $(IMAGE) image from local store"
	@echo "make clean  - remove all dynamically created files"
	@echo "make help   - display this help page"

# Log into DockerHub Docker repository.
login:
	$(info [info] logging into DockerHub repository)
	$(DOCKER) login $(DOCKER_REPOSITORY)

# Log out of DockerHub Docker repository.
logout:
	$(info [info] Logging out of DockerHub repository)
	$(DOCKER) logout $(DOCKER_REPOSITORY)

# Clone lando repository from SSITH and rebuild & deploy the tool.
# This results in resources/lando/lib to be created and populated.
resources/lando/lib lando:
	$(info [info] executing script clone-and-rebuild-lando.sh)
	./scripts/clone-and-rebuild-lando.sh

# Create Docker image.
image: resources/lando/lib
	$(info [info] rebuilding $(IMAGE) Docker image ...)
	$(DOCKER) build -t $(IMAGE) . $(DOCKER_BUILD_ARGS)

# Save Docker image locally to a .tar file.
save:
	$(info [info] saving Docker image to $(IMAGE).tar ...)
	$(DOCKER) save -o $(IMAGE).tar $(IMAGE)

# Pull Docker image from DockerHub private repository.
pull: login
	$(DOCKER) pull $(DOCKER_ORGANIZATON)/$(IMAGE):latest

# Push Docker image to DockerHub private repository.
push: login
	$(DOCKER) image tag $(IMAGE) $(DOCKER_ORGANIZATON)/$(IMAGE):latest
	$(DOCKER) push $(DOCKER_ORGANIZATON)/$(IMAGE):latest

# Push Docker image from local image cache / store.
remove:
	$(info [info] removing $(IMAGE) image locally ...)
	$(DOCKER) rmi $(IMAGE)

# Clean up all dynamically generated files, including lando clone.
clean:
	$(info [info] cleaning up all dynamically generated files ...)
	rm -rf repository resources/lando/lib
	rm -f $(IMAGE).tar

PHONY: all help login logout lando image save pull push remove clean

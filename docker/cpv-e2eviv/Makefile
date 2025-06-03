################################################################################
# Makefile to build and deploy the Free & Fair CPV Docker image, © Free & Fair #
################################################################################

# Organization within the Docker repository to push to.
DOCKER_ORGANIZATION := freeandfair

# Name of the Docker image to be created.
IMAGE=cpv-e2eviv

# Image platform(s) to build
IMAGE_PLATFORM=linux/amd64

# Docker-compatible command to use.  A standard alternative is `podman`.
# Override via an environment variable (e.g., "make DOCKER=podman ...").
DOCKER=docker

# Different command line options for Podman, in the event that we
# need them. This was inspired by trying to fix a build problem, and
# even though it doesn't do anything right now it might in the future.

DOCKER_VERSION := $(shell $(DOCKER) --version)
DOCKER_OR_PODMAN := $(firstword $(DOCKER_VERSION))
DOCKER_BUILD_ARGS=--platform=$(IMAGE_PLATFORM) --attest type=provenance,mode=max --attest type=sbom
ifeq ($(DOCKER_OR_PODMAN), podman)
	# For Podman, we don't use Docker-specific attestation or SBOM options
	DOCKER_BUILD_ARGS=--platform=$(IMAGE_PLATFORM)
endif

# Default target: help
all: help

# Display a brief help page listing possible commands/targets.
help:
	@echo "This Makefile supports the following targets:"
	@echo ""
	@echo "help (default) - display this help page"
	@echo "login          - log user into DockerHub repository"
	@echo "logout         - log user out of DockerHub repository"
	@echo "image          - create $(IMAGE) image (in local store)"
	@echo "save           - save $(IMAGE) image to a tar file"
	@echo "pull           - pull cpv-e2eviv image from DockerHub repository"
	@echo "push           - push cpv-e2eviv image to DockerHub repository"
	@echo "remove         - remove $(IMAGE) image from local store"
	@echo "clean          - remove all dynamically created files"

# Log into DockerHub.
login:
	$(info [info] logging into DockerHub)
	$(DOCKER) login

# Log out of DockerHub.
logout:
	$(info [info] Logging out of DockerHub)
	$(DOCKER) logout

# Create Docker image.
image:
	$(info [info] rebuilding $(IMAGE) Docker image ...)
	$(DOCKER) build -t $(IMAGE) . $(DOCKER_BUILD_ARGS)

# Save Docker image locally to a .tar file.
save:
	$(info [info] saving Docker image to $(IMAGE).tar ...)
	$(DOCKER) save -o $(IMAGE).tar $(IMAGE)

# Pull Docker image from DockerHub repository.
pull: login
	$(DOCKER) pull --platform=$(IMAGE_PLATFORM) $(DOCKER_ORGANIZATION)/$(IMAGE):latest

# Push Docker image to DockerHub repository.
push: login
	$(DOCKER) image tag $(IMAGE) $(DOCKER_ORGANIZATION)/$(IMAGE):latest
	$(DOCKER) push $(DOCKER_ORGANIZATION)/$(IMAGE):latest

# Remove Docker image from local image cache / store.
remove:
	$(info [info] removing $(IMAGE) image locally ...)
	$(DOCKER) rmi $(IMAGE)

# Clean up all dynamically generated files.
clean:
	$(info [info] cleaning up all dynamically generated files ...)
	rm -f $(IMAGE).tar

PHONY: all help login logout image save pull push remove clean

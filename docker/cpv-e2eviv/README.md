# Cryptographic Protocol Verification Docker Image

This folder contains everything needed to build and run the Free & Fair cryptographic protocol verification Docker image. For now, this image only includes Tamarin and its dependencies; if we decide to use other tools (e.g., ProVerif) for protocol assurance, we will add them later.

Note that it is _far_ less efficient to run Tamarin within Docker than it is to run it natively on your hardware; Tamarin is aggressively multi-threaded and consumes large amounts of memory, so we _strongly_ recommend installing Tamarin locally instead of relying on this Docker image; the primary motivation for this image is to provide a uniform environment for running CI/CV (e.g., in GitHub actions).

Note also that we currently only build this image for `linux/amd64`, because there is no straightforward way of building Tamarin for `linux/arm64`. It will therefore likely be _extremely slow_ on Apple Silicon systems.

## Prerequisites

Building the image requires the following:

- make
- [Docker](https://docker.com/) or Docker-compatible tools, such as [Podman](https://podman.io/)

In order to use/run the Docker image from the [Free & Fair Dockerhub](https://hub.docker.com/repository/docker/freeandfair/cpv-e2eviv) repository, the only prerequisites are:

- Docker or Docker-compatible tools

## Building the Docker Image

The build process is simplified via a *Makefile*.  Typing `make` will show the build targets, which are self-explanatory; `make image` builds the image.

## Deploying the Docker Image

In order to deploy the Docker image, use the make command `make push` after building the image.  This command requires the user to log into [DockerHub](https://hub.docker.com/) and to be a member of the [FreeAndFair](https://hub.docker.com/orgs/freeandfair) DockerHub organization with appropriate permissions to push into the [freeandfair/cpv-e2eviv](https://hub.docker.com/repository/docker/freeandfair/cpv-e2eviv) image repository.  The build target performs that login automatically before pushing, but it can also be triggered manually via `make login` (to log in) and `make logout` (to log out).

## Executing the Docker Image

To run the Docker image interactively, invoke:
```
docker run -it -v "$(PWD):/work" -w "/work" freeandfair/cpv-e2eviv
```
This maps the current working directory to `/work` inside the image, so it can be read from and written to by the tools. If you build the image locally and do not push it to DockerHub, use `cpv-e2eviv` instead of `freeandfair/cpv-e2eviv`.

## Vulnerabilities Reported by Docker Scout

As of this writing, Docker Scout does not flag any issues with this image.

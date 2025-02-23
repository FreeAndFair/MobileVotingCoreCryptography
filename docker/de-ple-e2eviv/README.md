# DE/PLE Docker Image

This folder contains everything needed to build and run the Free & Fair DE/PLE docker image for *Rigorous Digital Engineering*. The tools included in this image are [Lando](https://github.com/GaloisInc/BESSPIN-Lando) (for Domain Engineering) and [Clafer](https://www.clafer.org/p/software.html) (for Product Line Engineering). We also include the three web-based Clafer IDEs: **ClaferMooVisualizer**, **ClaferConfigurator**, and **ClaferIDE**, exposed via ports 8092, 8093, and 8094 while a docker container for the image executes.

## Prerequisites

In order to rebuild the docker image, we must have installed the following:
- git, make and [Maven](https://maven.apache.org/) (`mvn`)
- [OpenJDK 17](https://jdk.java.net/archive/) (to rebuild lando from source)
- Docker tools for the respective OS

On MacOS, it is recommended to install these tools via [Homebrew](https://brew.sh/): `brew install git make maven`

---

In order to use/run the docker image from the [Free & Fair Dockerhub](https://hub.docker.com/repository/docker/freeandfair/de-ple-e2eviv) repository, only
- Docker tools for the respective OS

ought to be needed.

## Building the Docker Image

The build process is simplified via a *makefile*. Simply typing `make` will build the respective `de-ple-e2eviv` image locally. The following commands are supported by the makefile:

```
make [all]  - clone and rebuild lando and create de-ple-e2eviv image
make login  - log user into dockehub repository
make logout - log user out of dockerhub repository
make lando  - clone and rebuild lando (prerequisite for building)
make image  - create de-ple-e2eviv image (in local store)
make save   - save de-ple-e2eviv image to a tar file
make pull   - pull de-ple-e2eviv image from dockerhub repository
make push   - push de-ple-e2eviv image to dockerhub repository
make remove - remove de-ple-e2eviv image from local store
make clean  - remove all dynamically created files
make help   - display this help page
```

When creating the image locally, i.e., via `make` or `make all`, the Lando tool sources will be automatically cloned from the public [https://github.com/GaloisInc/BESSPIN-Lando](https://github.com/GaloisInc/BESSPIN-Lando) BESSPIN GitHub repository and the Lando tool is recompiled to produce a fresh JAR for deployment into the image. The [clone-and-rebuild-lando.sh](./scripts/clone-and-rebuild-lando.sh) inside the `scripts` folder facilitates this task. We currently use commit hash `db552ec74d4532611280693438207a72a23045b4` of the `develop` branch as baseline for deployment, being the latest Galois development version on August 2, 2024. Since Lando does not have a periodic release cycle, we have to change this tag manually in the future by updating the `clone-and-rebuild-lando.sh` script if we like to deploy a newer version of Lando via the docker image.

We note that the build process is engineered in such a way that all Lando and Clafer tools are dynamically fetched from the WWW during each build. The archive in [downloads/clafer-tools-0.4.5-linux-x86_64.zip](downloads/clafer-tools-0.4.5-linux-x86_64.zip) is thus not actually needed by the Dockerfile or installation process — it is mostly there for reference and as a fallback if online access to the [Clafer 0.4.5 distribution binary](https://gsd.uwaterloo.ca/clafer-tools-binary-distributions) may be disabled or fail to work at some point in the future.

Note that `make` only builds the image locally and does not push it to the Free & Fair dockerhub repository yet. The image ought appear in the local docker store as `de-ple-e2eviv:latest` if the build process succeeds (execute `docker images` to verify this).

## Deploying the Docker Image

In order to deploy the docker image, the make command `make push` can be subsequently used. This requires the user to log into [dockerhub](https://hub.docker.com/) and to be a member of the [freeandfair](https://hub.docker.com/repository/docker/freeandfair) dockerhub organization with appropriate permissions to push into the [freeandfair/de-ple-e2eviv](https://hub.docker.com/repository/docker/freeandfair/de-ple-e2eviv) image repository. The makefile performs that login automatically before pushing, but it can also be triggered manually via `make login` (to log in) and `make logout` (to log out). The user will have to provide their dockerhub username and password at this point.

## Loading the Docker Image

Instead of using `make` to build the docker image dynamically, it is possible to load the docker image via the

```
docker load -i de-ple-e2eviv.tar
```

command, assuming the `de-ple-e2eviv.tar` has first been downloaded from a suitable location. In that case, follow the same steps for executing the docker image locally, as explained in the next section.

## Executing the Docker Image

There are two ways to run the docker image: either locally or from the Free & Fair dockerhub remote repository. For each of these a script is provided, namely inside the `scripts` folder:
- [`run-ple-local.sh`](./scripts/run-ple-local.sh)
- [`run-ple-remote.sh`](./scripts/run-ple-remote.sh)

Running the image locally (`run-ple-local.sh`) requires that it needs to be either loaded or built first, as described above. Running the image from the Free & Fair dockerhub repository (`run-ple-remote.sh`) does **not** require any prerequisite load or build: only the script itself is required as well as the necessary credentials for dockerhub, membership to the Free & Fair organization on dockerhub, and permission to access the [de-ple-e2eviv](https://hub.docker.com/repository/docker/freeandfair/de-ple-e2eviv) private image repository contained therein.

Note that when executing `run-ple-remote.sh` from the command line, the user will initially have to provide access credentials for dockerhub in order to log into that repository. Afterwards, the image ought be downloaded and run automatically. Running locally does not require any access credentials, only that the image must have previously been built or loaded.

We note that both scripts perform some additional setup to expose ports 8092, 8093 and 8094 in order to make the various Clafer WEB IDEs available: **ClaferMooVisualizer**, **ClaferConfigurator**, and **ClaferIDE**. While the container is running, the IDEs can be access from the host via typing the URLs `localhost:8092`, `localhost:8093` and `localhost:8094` into one's favorite web browser.

Inside the docker container, the following command-line tools are available: `lando`, `clafer` and `claferIG`. To make it easy to use those tools from the host file system, the scripts map the current directory as `/work` into the container. Thus it is recommended first to change to the location from where we want to run the tools on the host, and then execute the scripts from there (they may be added permanently to PATH). Both scripts ought be agnostic to where they are executed from.

We note that the container is run interactively by the scripts and is automatically destroyed after exiting the image, i.e., via typing `exit`. Inside the container, all tool installations can be found under `/opt`.

## Miscellaneous Information

The `de-ple-e2eviv` image is built for the `linux/amd64` platform, so we do not expect any issues when running it in an Linux environment and on Intel architecture, or in the GitHub/GitLab CI.
We have not produced an `arm64` image for macOS on Apple Silicon because [Docker Desktop for Mac](https://docs.docker.com/desktop/install/mac-install/) can execute `amd64` images via [Rosetta 2](https://developer.apple.com/documentation/apple-silicon/about-the-rosetta-translation-environment) emulation.
Should a multi-platform image be desired in the future, please contact the Free & Fair RDE team, preferably [Daniel Zimmerman](mailto:dmz@freeandfair.us?subject=RE%3A%20Help%20with%20DE%2FPLE%20docker%20image) or [Frank Zeyda](mailto:frank.zeyda@freeandfair.us?subject=RE%3A%20Help%20with%20DE%2FPLE%20docker%20image).

Lastly, any issues or bug reports ought be noted to [Frank Zeyda](mailto:frank.zeyda@freeandfair.us?subject=RE%3A%20I%20found%20a%20bug%20in%20the%20DE%2FPLE%20docker%20image).

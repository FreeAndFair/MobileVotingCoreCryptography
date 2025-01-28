# Continuous Integration, Deployment, and Verification (CI/CD/CV)

This document contains general information about the continuous integration (CI), continuous deployment (CD), and continuous verification (CV) practices of this project, and specific information about what artifacts are currently, and are planned to be, checked, generated, and verified using CI/CD/CV processes.

## Continuous Integration

Continuous integration is meant to check that everything in the repository (that can be reasonably checked) has correct syntax, builds correctly without errors (and, depending on how pedantic we are for any given artifact, without warnings), and fulfills any other requirements of the project or the repository that can be automatically checked. Examples include ensuring that LaTeX documents can compile and generate PDFs, ensuring that Lando and Clafer models can be parsed, ensuring that Clafer models can generate instances, etc. Continuous integration processes are typically run on every commit to a pull request branch, and on every commit added to `main` or a release branch.

The artifacts that are currently subject to continuous integration, the checks that are done, and the mechanisms by which that occurs are:

- Lando files (`*.lando`) are checked for syntactic validity, by running `lando validate` within our [PLE docker container](../docker/de-ple-e2eviv). This occurs for changed Lando files in pull request commits (via GitHub action workflow [Test Validity of Changed Lando Files](../.github/workflows/test-validity-of-changed-lando-files.yml)) and for all Lando files in the repository on every push to `main` (via GitHub action workflow [Test Validity of Lando Files](../.github/workflows/test-validity-of-lando-files.yml)).
- Clafer files (`*.cfr`) are checked for syntactic validity, by running `clafer` within our [PLE docker container](../docker/de-ple-e2eviv). This occurs for changed Clafer files in pull request commits (via GitHub action workflow [Test Validity of Changed Clafer Files](../.github/workflows/test-validity-of-changed-clafer-files.yml)) and for all Clafer files in the repository on every push to `main` (via GitHub action workflow [Test Validity of Clafer Files](../.github/workflows/test-validity-of-clafer-files.yml)).
- All targets of the [Clafer feature model](../models/feature_model)'s [makefile](../models/feature-model/makefile) are built (again, within our [PLE docker container](../docker/de-ple-e2eviv)) on every pull request commit that changes anything within the feature model's directory and on every push to `main` (via GitHub action workflow [Run Makefile for Clafer Model](../.github/workflows/run-makefile-for-clafer-model.yml)).

The following artifacts that have not yet been merged into the repository are already subject to continuous integration in their branches:

- All targets of the threat model's makefile are built on every pull request commit that changes anything within the threat model's directory. This ensures that the threat model database can be built, and that the static threat model document can be built. The threat model diagrams are _not_ regenerated during continuous integration, because some of them require macOS and OmniGraffle to build, and their rendered versions are stored in the repository.

The following artifacts are not yet subject to continuous integration, but we plan to implement it as we build and integrate these artifacts into the repository:

- The paper about refinements among high-level models, and any other buildable documents that we write, will be checked for buildability on every commit that changes the document source or build process.
- Cryptol, Tamarin, and ProVerif files will be checked for at least syntactic correctness. They will also be tested to the extent that is practical; any testing of Tamarin will require proof scripts, as its automatic prover is too resource-intensive to run in CI.
- Rust implementations will be built and their test suites will be run.

## Continuous Deployment

Continuous deployment is meant to ensure that a set of artifacts both can be generated and is made available for download (rather than forcing individuals to regenerate it themselves). Such a set of artifacts for a project is called a "release" (though in most cases, for this project, it will be a "development release" that is just a checkpoint of the current `main`). These generated artifacts may include rendered documents (e.g., PDFs from LaTeX sources, PDFs or Markdown documents from Lando sources), executable code, etc.

No artifacts in this repository are currently subject to continuous deployment. However, the repository for the [Free & Fair Code Standards](https://github.com/FreeAndFair/CodeStandards), a multi-file LaTeX document, deploys a rendered version of the code standards to its [Latest release](https://github.com/FreeAndFair/CodingStandards/releases/tag/latest) every time a change to the document is pushed to `main`.

We plan to implement continuous deployment to generate a hyperlinked representation of the Lando domain model, and perhaps also the Clafer feature model. We may also implement continuous deployment for our current, and any future Docker containers, though that would be to [the Free & Fair DockerHub repository](https://hub.docker.com/repositories/freeandfair) rather than part of a GitHub release.

In addition, the following artifacts that have not yet been merged into the repository are planned to be subject to continuous integration:

- The static threat model document will be generated and made available.
- The paper about refinements among high-level models will be generated and made available.
- Our SysMLv2 system and network architecture model will be rendered and made available.
- Any other similar documents we write will be generated and made available.

## Continuous Verification

Continuous verification is meant to ensure that the artifacts in the repository satisfy some correctness criteria, via execution of either generated or hand-written test suites and static formal verification routines. We currently do not have any artifacts in the repository that are subject to continuous verification. The artifacts on which we plan to perform continuous verification are:

- Cryptol implementations of cryptographic algorithms
- Tamarin/ProVerif descriptions of cryptographic protocols
- Rust implementations of the various components of the cryptographic core library

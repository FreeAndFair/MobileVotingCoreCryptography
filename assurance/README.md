# Assurance Case

This directory contains the current assurance case for the system (at present, this is only a skeleton) in a form that can be imported into version 0.51.0-s of the NASA AdvoCATE tool (see https://nari.arc.nasa.gov/sws-tc3-diagram/capability/advocate/), as well as scripts to generate the skeleton of the assurance case from the [threat model](../models/threat-model). AdvoCATE is a comprehensive assurance case tool for cyberphysical systems, and as such has many features we do not need to use for this project. The following describes how we have mapped our threat model's security objectives, attacks and mitigations into AdvoCATE's various artifacts:

- [`E2E-VIV_FunctionalArchitecture.functionalarchitecture`](advocate-project/E2E-VIV_FunctionalArchitecture.functionalarchitecture) is the AdvoCATE "functional architecture" of the system. In it, the "functions" are not actually functions carried out by the system, but rather _high-level security objectives_ that the system is meant to maintain (e.g., `availability` and `correctness`). These are linked to "deviations", each of which represents the negation of a more specific security objective (e.g., violation of the objective "Each cryptogram recorded in the BB is identical to a cryptogram cast by the VA."). The functional architecture also contains functions for `core`, `non-core`, and `partially-core` to roughly represent functional areas of a potential system in which mitigations can be implemented; creating an entire system architecture in AdvoCATE would have limited benefit for us because we are not implementing a cyberphysical system. This file is generated directly from the threat model database.

- [`E2E-VIV_SafetyArchitecture.safetyarchitecture`](advocate-project/E2E-VIV_FunctionalArchitecture.safetyarchitecture) is the AdvoCATE "safety architecture", or "hazard log". It catalogs all the potential attacks against the system (as defined in the threat model) and links them to the security objectives in the functional architecture that they affect, and the mitigations that are relevant to each. We do not currently have likelihood/severity information in the threat model, so all hazardous activities in the hazard log end up with default (low) likelihood, severity, and risk; if and when we add such information to the threat model, we can augment the script to generate a safety architecture that includes it. This file is generated directly from the threat model database, and can be generated in two different ways: one uses exactly the security objectives listed in the threat model for each attack as the deviations caused by that attack; the other also includes _implied_ security objectives (that is, an attack against a security objective is also considered to be an attack against all its ancestors and descendants in the security objective tree).

- [`E2E-VIV_Requirements.requirements`](advocate-project/E2E-VIV_FunctionalArchitecture.safetyarchitecture) is the AdvoCATE "requirements log". For our assurance case, this represents not the system's functional requirements (as described in the [domain model](../models/domain-model/requirements)), but rather the set of mitigations that must be implemented in order to protect against the hazards described in the hazard log. There is one "requirement" per individual mitigation, and these are linked to the various attacks in the hazard log and to the various mitigation implementation goals in the argument log. This file is generated directly from the threat model database.

- [`E2E-VIV_Argument.argument`](advocate-project/E2E-VIV_Argument.argument) is the AdvoCATE "argument", which relates pieces of assurance evidence to the requirements (that is, the implementation of the various system mitigations). The structure of the argument is such that, once it is complete, we will have shown that (1) all mitigations that must be implemented entirely by the core cryptographic library have been implemented correctly, and (2) all mitigations that require support from the core cryptographic library have that support in place. The skeleton of this file is generated from the threat model database, but it must then be extended by hand to incorporate the actual assurance evidence we create during implementation and validation.

## Building

It is not (generally, but see below) necessary for you to run any of the scripts included here; however, should you wish to regenerate the AdvoCATE skeleton (if, for example, you change the threat model and want to keep the skeleton in sync), run `make help` for information on the various provided build targets.

### Python Requirements

The Python `requirements.txt` file for the scripts is alongside them in the [scripts](./scripts) directory. The scripts require Python 3.12 or higher, because they take advantage of the enhancements of [PEP-701](https://peps.python.org/pep-0701/) for formatted string parsing.

## Usage

To load the included assurance case into AdvoCATE, you can import the [`advocate-project`](./advocate-project) directory as an AdvoCATE project as follows:

- Select the "Import..." menu option
- Select "Existing Projects into Workspace" in the import window
- Select this directory ([`assurance`](.)) in the "Select root directory" box, and you should see `advocate-project` listed.
- (STRONGLY RECOMMENDED) Ensure that "Copy projects into workspace" is checked, so that your use of AdvoCATE modifies a clean copy of the files rather than the files in your checked-out Git repository; any changes you make can be copied into the Git repository later should you need to commit them, but making such changes outside the repository can prevent unnecessary/annoying Git issues.
- *Be sure to wait* until the project is fully imported and all internal representations have been generated before exploring the AdvoCATE project. You can tell that this is the case by looking at the Eclipse task status progress bars (or just waiting until AdvoCATE stops using large amounts of CPU cycles). If you try to explore the project before AdvoCATE has finished computing its internal representations from the imported project (which currently does not include them), the results may be unintuitive and/or unpredictable.

With the current version of AdvoCATE as of this writing (`0.51.0-s (Parsons Peak)`), once the project is imported, there can be (in our experience, there often are) issues with the imported project not realizing that it has the various assurance case components; this generally results in the components not being visible on the dashboard (e.g., it reports that there is no hazard log or argument), and Java exceptions being raised when files are opened (e.g., double-clicking on the safety architecture in the model explorer when the project is in such a state causes a `NullPointerException` to be displayed in the editor). We speculate that this is a race condition or some similar issue with respect to AdvoCATE generating its internal representations on initial import of large, generated projects. If you import the project and find that you cannot see components like the hazard log or argument on the project's dashboard, or encounter Java exceptions while exploring te project, try the following:

1. Close the dashboard and any other open files.
2. Remove all files except `representations.aird` from the project, using AdvoCATE's interface (select them, right-click, select "Delete", and approve the deletion).
3. Close and re-open the project.
4. Drag all files except `representations.aird` using your graphical file system viewer (macOS Finder, Windows Explorer, etc.) from the Git repository to the project's top level in AdvoCATE, and select "Copy files" when prompted. Alternatively, you can use `cp` on the command line to copy the files from the Git repository into the AdvoCATE workspace project directory (e.g., `cp advocate-project/E2E-VIV* my_advocate_workspace/advocate-project`) and then "Refresh" the project inside AdvoCATE.
5. Close and re-open the project.
6. Open the project dashboard.

## Scaling Issues

The AdvoCATE tool does not scale well with complex hazard logs. As a result, it is slow when manipulating either automatically-generated hazard log, but especially so with the one including implied security objectives; here are some representative operation timings on a MacBook Pro M3 Max with 64GB of RAM; (s) and (l) timings are for the "small" (without implied security objectives) and "large" (with implied security objectives) hazard logs, respectively:

| Operation                                                            | Time (s) | Time (l) |
| -------------------------------------------------------------------- | -------- | -------- |
| Initially import the project                                         | ~35s     | ~2m40s   |
| Fix a broken import (step 4, with command line copying and refresh)  | ~35s     | ~2m40s   |
| Open the (non-broken) project, or launch the app with it open        | ~35s     | ~2m40s   |
| Open the hazard log table editor                                     | ~5s      | ~30s     |
| Open the DSL for a representative hazardous activity                 | ~15s     | ~1m15s   |

At the time of this writing, the generated hazard log is ~280KB without implied security objectives, and ~580KB with them (other artifacts also become larger, but not nearly as much). More importantly, as shown in the table above, it takes substantially more time for AdvoCATE to process the larger version, and operations on it take several times as long. AdvoCATE also generates more than twice as much internal representation (~12MB vs. ~24MB). The version included in the assurance case in this repository is the version without implied security objectives; to use the version with implied security objectives instead, run `make update_implied` before importing the assurance case into AdvoCATE to update the "static" parts of the assurance case (the functional and safety architectures and the requirements) with the implied security objectives, while leaving the argument and any additional supporting files intact.

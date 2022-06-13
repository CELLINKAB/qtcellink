

# Contribution guidelines

Do you want to contribute to this project? Nice!

Then you should abide by the following guidelines which will make collaboration easier for everyone!

## Submitting a piece of work

* **Read through this entire document first!**
* Yes, really! :)
* Check out the branch you want to base your work on, which is usually dev, but sometimes a release or hotfix branch. 
  (see below for more details about branches)
* Create a new branch referring to the jira issue you are working on (i.e. issues/BIOX-123_crash_after_print_complete).
  * Set the 'Fix version' field if not set.
   * Use -dev if your PR targets the dev branch, otherwised -x.y.z for the corresponding release/hotfix branch.
   * If no such version exists, create one or ask one to be created.
   * For this, HeartWare repo, use either "DNA Studio-xxx" and/or "HeartOS-xxx", depending on the impact of your change. 
* Make changes and commit locally.
* Push branch to [GitHub](https://github.com/CELLINKAB/HeartWare/).
  * Our preferred branch name template is `issues/BIOX-xxx_this_fixes_that`
* Create a [GitHub pull request](https://github.com/CELLINKAB/HeartWare/pulls) targeting the right branch.  
  (Mark the PR as draft if you just want to see how it builds, or get some early comments/reviews from colleagues).
* Add any reviewers that you feel should take a closer look, or leave empty.
* Move the Jira issue into 'Code Review'.
* Wait for other developers to review, but feel free to send them the PR link in chat as well.
* Update your code with any comments given.  
  * Ask questions if you think something is unclear or unreasonable.  
  * Be sure to address any comments even if you got "approved", it means "looks good, but this need to be fixed before PR".
  * Mark comments as **resolved** as you go through and fix them, while giving an explaining comment answering any questions asked.
* Push new commits without rebasing anything so reviewers can see your gradual changes.
* When all comments have been resolved and all checks pass, you can merge.
  * Use squash if it's a small, single item change.
  * Use rebase if you want to keep the commit history (i.e. first a refactoring commit, then the actual fix).
  * Use merge **only** if your branch is one of the long-term branches, i.e. release/x.y.z. -> dev.
    When doing these types of merge, you often want to keep the source branch around afterwards,
    so be sure to restore it in GitHub if that is the case.  
    (The only exception is when doing the final release->master merge for actually doing a release,  
    In those cases we don't want to keep that release branch anymore.)
 * Move the jira issue to 'Testing'
   * If it is an issue that be tested by QA, you are done.
   * If it is an issue that can only be tested by a developer (CI change, refactoring, debug/logging fix, etc), 
     add the 'DevTest' label to it.

**NOTE:** Do not ever merge dev to a release branch, unless the entire team agrees that we are in a sticky situation
and this is the best way out and it will not cause problems.  
(Use cherry-pick instead if you need to move specific commits from dev to a release branch.)

## Git history/commit guidelines

* Try to address one thing per commit
* Avoid mixing refactoring commits with bugfixes or new features
* If you don't have a long running branch or something with merges from your target, 
  rebase your changes on top of the target branch.
* Consider curating/cleaning your commit history (with git interactive rebase) after having fixed PR comments.
  (Using a good GUI based Git client helps to see what you have and what you want to do,  
   even if you use the command line to do the actual operations)

## Branches and workflow

Make sure you work with and target the correct branch, depending on what your goal is!

Quick overview:

* New features go on the *dev* branch.
* If we are stabilizing, we merge changes to a *release* branch.
* The last (customer/production) release is on *master* branch, and almost never has direct commits, only merges from release.

A recommendation is to setup your git config to rebase, not merge, on pull.  
(This works most of the time, but make sure you don't accidentally rebase your local version of a long-running branch like dev)

### Gitflow

We use [gitflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow) more or less.

The main points of the GitFlow branching model are:

**TODO:** Rename 'master' branch to 'main'

* The *dev* branch is created from *master*
* A *release* branch is created from *dev* (usually with release number suffix, i.e. release/3.2.0)
* *Feature* branches are created from *dev*
* When a *feature* is complete it is merged (or rebase/squashed) into/onto the *dev* branch
* When the *release* branch is done it is merged into *dev* and *master*
  (*release* branches can acutally be merged to *dev* continously )
* If an issue in *master* is detected, a *hotfix* branch is created from *master*
* Once the *hotfix* is complete it is merged to both *dev* and *master*

A Gitflow commit history tree can look like this:

![Gitflow chart](https://wac-cdn.atlassian.com/dam/jcr:a9cea7b7-23c3-41a7-a4e0-affa053d9ea7/04%20(1).svg?cdnVersion=1460)

### Branch names

**TODO:** Delete and/or move old branches into the old/ prefix

* master -> released to customers/production
* dev -> next minor version x.Y.z, or major version when that is appropriate
* release/x.y.z -> stabilization work in progress
* hotfix -> next patch version x.y.Z
* issues/[jira-id]_[description] -> feature/bugfix branches  
  (these are only built when a pull request is created on github.)
* old/ -> stale branches that we don't want to delete just yet

### Build names, version numbers and suffixes

The version number is computed by GitVersion, one for DNA Studio 3 (and, soon one for HeartOS).

* builds on 'dev' get the alpha suffix, i.e. XXX-3.2.0-alpha.17 (has new features and changes, potentially unstable)
* builds on 'release' get the beta suffix, e. XXX-3.2.0-beta.3
  (should be more and more stable, very few - if any - new things)
* builds on 'master' get no suffix, simply XXX-3.2.0

## Coding guidelines

Adapted from https://github.com/CELLINKAB/communication-module/blob/develop/CONTRIBUTING.md

[//]: # (Use :heavy_check_mark: or :x: to denote rows enforced, or not, by CI.)

| Guideline | Enforced by CI | Rationale/Comment |
|:-----------|:----------------:|:-----------|
| Write [good commit messages](https://chris.beams.io/posts/git-commit/) and include the JIRA issue number and github PR number. | :x: | Increase maintainability |
| Comment your code in a way that will allow others to understand it... a year later. | :x: | Increase maintainability & easier onboarding |
| Document all classes and functions using [doxygen-like](http://www.doxygen.nl/manual/docblocks.html) syntax. | :x: | Create automatically generated documentation |
| Maintain the naming conventions, within each file and throughout the project, and choose clear names for classes/methods that document themselves. | :x: | Increase readability |
| Maintain the format conventions, within each file and throughout the project. | :x: | We plan to use [clang-format](https://clang.llvm.org/docs/ClangFormat.html) at some point. |
| Write *atomic* unit tests with human readable names which clarify the business value they assert. | :x:  | Increase readability, document behaviour |
| Follow the [C++ core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines). | :x: | Check 'cppcoreguidelines'  with 'clang-tidy' |
| Follow the [dependency inversion principle](https://en.wikipedia.org/wiki/Dependency_inversion_principle). | :x: | Code against interfaces not implementations |
| Prever the [PIMPL pattern](https://en.cppreference.com/w/cpp/language/pimpl) for classes with long-lived objects and lots of privates | :x: | Faster (re-)compilation, less coupling and more encapsulation |
| Do not use a standardized prefix or suffix for interfaces.  Give them a name that reflects the functionality they abstract. | :x: | Saying that an interface is an "interface" is a [tautology](https://softwareengineering.stackexchange.com/a/117393). |
| I prefix is allowed for pure interfaces | :x: | Clarifies multiple concrete vs interface inheritance |
| Test functionality, especially when not covered by unit tests, on hardware. | :x: | It is a good idea to verify changes on hardware, but a *must* when functionality cannot be unit tested. |
| Use *camelCase* for function and variable names | :x: | Coding style convention |
| Use *PascalCase* for class and struct names | :x: | Style convention |
| Use *UPPER_CASE* for constants | :x: | Style convention |
| Prefix member variables names with `m_` | :x: | Style convention |
| Prefix static member variables names with `ms_` | :x: | Style convention |
| Prefix global (or function static) names with `s_` | :x: | Style convention |
| Do not use abbreviations in code or documentation unless they are common knowledge | :x: | Increase clarity & readability |

### Guidelines not yet implemented

| Guideline | Enforced by CI | Rationale/Comment |
|:-----------|:----------------:|:-----------|
| Do not decrease the code coverage below the lower acceptable limit. | :x: | Test all code that makes sense to be tested  |


## Continuous integration

All GitHub PRs are required to have the checks passed, one for each target environment typically.

### Windows

We currently use [Azure DevOps](http://dev.azure.com/Cellink/Heartware).

The pipeline is described in [azure-pipeline.yml](./azure-pipeline.yml).

The windows build is run with our own build agent VM hosted on AWS, since it uses ~2GB of git-lfs binaries that we need to have cached, and it takes 5-8 minutes to build with 16 cores, so the default runners (2 cores) are too underpowered.

The Windows pipeline builds and tests everything, but only publishes the 'DNA Studio 3' installer as an artifact.

### Linux

We use [Jenkins](http://jenkins.dev.cellink.com:38080/job/BIO-X/job/HeartWare/) to build and run all tests.

For the HeartOS part (i.e. embedded UI), see [the various rpi3 projects](http://jenkins.dev.cellink.com:38080/job/BIO-X/view/BioX/) on Jenkins, of which this repo is included as a submodule.

### Max OS X

**TODO:** Handle this when we get to it.

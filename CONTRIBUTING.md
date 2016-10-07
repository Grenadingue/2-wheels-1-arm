# Contributing

## Rules
### Branches
#### Creation
A UNIQUE branch MUST be created to resolve an issue.

The name of the branch MUST be composed of:
* A `#`
* The id of the issue processed
* The name of the branch (with space replaced by underscores)

See example section below.

#### `master` branch
You MUST NOT push directly on `master`. This branch should contain only functionnal work. This is the release/production branch. You MUST use the pull-requests to add your work to this branch, see below.

### Commits
#### Message
To let github reference the commits inside the issues, the commit messages MUST be composed of:
* A `#`
* The id of the processed issue
* A `:`
* A space
* Your commit message

See example section below.

### Pull-requests
#### Submission
* On the repository main page, just upside the file listing, select the branch you want to submit for a pull-request
* Just on the right of the branch name, click on "New pull request"
* Then "Create pull request"

#### Validation
I will validate your pull requests manually.

#### Merge with `master`
Once a pull request is made and validated, you will be able to click on the merge button. Who will merge the desired branch onto `master`.

## Example
* I'm processing the [20th issue "Add contrubting instructions"](https://github.com/Grenadingue/2-wheels-1-arm/issues/20)
* I created the branch named `#20_add_contributing_instructions`
* I made a commit with this message `#20: Add CONTRIBUTING.md with contributing instructions and example`
* This commit is automatically referenced in the [issue interface](https://github.com/Grenadingue/2-wheels-1-arm/issues/20)
* I select my branch in the github interface
* I click on create a pull request
* The [pull request](https://github.com/Grenadingue/2-wheels-1-arm/pull/21) is now visible in the [pull requests tab](https://github.com/Grenadingue/2-wheels-1-arm/pulls)
* I wait for the pull request validation
* I merge the pull request onto master
* I delete the pulled branch

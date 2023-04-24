# Contributing to AI Library
First of all, thank you for considering contributing to the AI Library project! We appreciate your time and effort, and we're excited to have you on board. As a graduate and the sole programmer on this project, your contributions can help improve the library and make it even more valuable to the community.

This document outlines the process for contributing to the project, including forking, creating issues, and submitting pull requests.

## Code of Conduct
Please read and follow our [Code of Conduct](CODEOFCONDUCT.md) to ensure a positive and welcoming environment for all contributors.

## Getting Started
1. Fork the repository: Click the "Fork" button on the top right corner of the project's GitHub page. This will create a copy of the repository under your own GitHub account.

2. Clone your forked repository to your local machine:
``` sh
git clone https://github.com/your_username/AI-Library.git
cd AI-Library
git submodule update --init --recursive
```
3. Add the original repository as a remote, so you can fetch the latest changes:
``` sh
git remote add upstream https://github.com/RyanWestwood/AI-Library.git
```

## Creating Issues
If you find a bug, have a feature request, or want to discuss something related to the project, please create a new issue using the appropriate issue template. Make sure to follow the guidelines in the template and provide enough information for others to understand and reproduce the problem or discuss the topic.

## Submitting Pull Requests
1. Ensure you have the latest changes from the main repository:
``` sh
git fetch upstream
git checkout main
git merge upstream/main
```

2. Create a new branch for your changes:
``` sh
git checkout -b feature/your-feature-name
```
Use a descriptive name for your branch, such as `feature/pathfinding-improvements` or `bugfix/memory-leak-fix`.

3. Make your changes, ensuring they follow the coding standards and guidelines for the project. Test your changes and make sure they don't introduce new bugs or break existing functionality.

4. Commit your changes, using clear and concise commit messages that explain the purpose of the commit:
``` sh
git add .
git commit -m "Your descriptive commit message"
```

5. Push your changes to your fork:
```sh
git push origin feature/your-feature-name
```

6. Create a pull request on GitHub:

* Go to the main repository's "Pull Requests" tab and click "New Pull Request".
* Choose the base repository (your_username/AI-Library) and the base branch (main).
* Choose your forked repository (your_username/AI-Library) and your feature branch.
* Click "Create Pull Request" and fill in the template with the relevant information.

7. Address any comments or requested changes from the maintainers. They may ask for additional details, changes, or tests to ensure the quality of the project.

## Tips
* Make sure your pull request includes tests and documentation for your changes.
* Keep your changes focused and limited to a single feature or bugfix.
* Engage in respectful and constructive discussions with the maintainers and other contributors.  

Once again, thank you for your interest in contributing to the AI Library project. Your efforts help make the library better for everyone, and we're looking forward to collaborating with you!
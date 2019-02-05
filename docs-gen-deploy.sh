#!/bin/sh
# Shell script to automatically generate and deploy docs using Doxygen.
# Travis CI requires a 'full access to private repositories' token,
# which can be obtained on GitHub. Afterwards, it must be input
# in the Travis CI settings section for that repository's page,
# as an environment variable called 'GH_REPO_TOKEN'.
# Source: https://gist.github.com/vidavidorra/548ffbcdae99d752da02
__AUTHOR__="Jeroen de Bruijn"
set -e
mkdir code_docs
cd code_docs
# Use the Token to gain access to the private repo.
git clone -b gh-pages "https://${GH_REPO_TOKEN}@${GH_REPO_REF}"
cd $GH_REPO_NAME
git config --global push.default simple
git config user.name "Travis CI"
git config user.email "travis@travis-ci.com"
rm -rf *
echo "" > .nojekyll
doxygen $DOXYFILE 2>&1 | tee doxygen.log
if [ -d "html" ] && [ -f "html/index.html" ]; then
    git add --all
    git commit -m "Deploy docs: ${TRAVIS_BUILD_NUMBER}" -m "Commit: ${TRAVIS_COMMIT}"
    git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}" > /dev/null 2>&1
else
    echo '' >&2
    echo 'Warning: No documentation (html) files have been found!' >&2
    echo 'Warning: Not going to push the documentation to GitHub!' >&2
    exit 1
fi
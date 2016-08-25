# tripal_jbrowse_api

A Tripal module that exposes Chado as a JBrowse-compatible REST API

Based on https://github.com/erasche/chado-jbrowse-connector

# Quickstart Guide

1. Install this module on your Tripal site
2. Visit `admin/people/permissions` on your site and give the **Use JBrowse API** permission to all roles.
3. Go to <http://jbrowse.org/code/JBrowse-1.12.1/?data=http://yourtripalsite.com/api/jbrowse/YourOrganismsCommonName> to see all the tracks that were automatically created from your Chado feature table!

# License

GPLv3. The queries in includes/tripal_jbrowse_api.queries.inc that are derived from the chado-jbrowse-connector project, which is licensed under AGPLv3, are included here from a GPLv3 licensed version of that project provided to me by Eric Rasche with the approval of the other contributors.

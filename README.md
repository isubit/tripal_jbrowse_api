# tripal_jbrowse_api

A Tripal module that exposes Chado as a JBrowse-compatible REST API

Based on https://github.com/erasche/chado-jbrowse-connector

# Quickstart Guide

1. Install this module on your Tripal site
2. Visit `admin/people/permissions` on your site and give the **Use JBrowse API** permission to all roles (including anonymous users).
3. Go to <http://jbrowse.org/code/latest-release/?data=http://yourtripalsite.com/api/jbrowse> to see all the tracks that were automatically created from your Chado features table!

# Customizing Permissions

Access to the API can be limited to authenticated users by removing the **Use JBrowse API** permission from the 'anonymouse user' role on the `admin/people/permissions` page. Please note that if you do this external JBrowse instances not hosted on the same server as your Tripal site will not be able access the data.

# Adding custom tracks

The [tripal\_jbrowse\_tracks module](https://github.com/isubit/tripal_jbrowse_tracks) integrates with this module and provides a content type for adding custom tracks.

# License

GPLv3. The queries in includes/tripal_jbrowse_api.queries.inc that are derived from the chado-jbrowse-connector project, which is licensed under AGPLv3, are included here from a GPLv3 licensed version of that project provided to me by Eric Rasche with the approval of the other contributors.

<?php

/**
 * Allows additional tracks to be added to the trackList.json endpoint
 *
 * @param $organism
 *   The organism object loaded from the endpoint URL
 *
 * @return array
 *   Additional tracks to expose to JBrowse
 *
 */
function hook_jbrowse_tracks($organism) {

  $data = array();

  $data[] = array(
    'category' => 'Tripal JBrowse Tracks',
    'label' => 'Tripal_ExampleTrackName',
    'type' => 'JBrowse/View/Track/CanvasVariants',
    'trackType' => 'JBrowse/View/Track/CanvasVariants',
    'key' => 'ExampleTrackName',
    'storeClass' => 'JBrowse/Store/SeqFeature/VCFTabix',
    'urlTemplate' => 'http://example.com/ExampleTrackName.vcf.gz',
  );

  return $data;

}

/**
 * Allows additional options to be added to the trackList.json endpoint
 *
 * @param $data
 *   The array of configuration and tracks to be sent by the trackList.json endpoint
 *   Keys guaranteed to be present:
 *     'refSeqs': the url of the refSeqs.json endpoint
 *     'tracks': array of tracks to expose, including those from hook_jbrowse_tracks
 *
 * @param $organism
 *   The organism object loaded from the endpoint URL
 */
function hook_jbrowse_tracklist_alter(&$data, $organism) {
  $data['aboutThisBrowser'] = array(
    'title' => 'Browser for ' . $organism->common_name,
    'description' => 'Example description',
  );
}
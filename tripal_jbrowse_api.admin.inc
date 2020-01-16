<?php

require_once 'includes/tripal_jbrowse_api.queries.inc';

/**
 * @file
 * Admin page callbacks for the tripal_jbrowse_api module.
 */

function tripal_jbrowse_api_settings() {

  $results = chado_query(TRIPAL_JBROWSE_API_QUERY_ALL_ORGANISMS)->fetchAll(PDO::FETCH_ASSOC);

  foreach ($results as $row) {
    $prefix = 'tripal_jbrowse_api_' . $row['organism_id'] . '_';
    $form['organism_' . $row['organism_id']] = array(
      '#type' => 'fieldset',
      '#title' => sprintf('%s %s (%s)', $row['genus'], $row['species'], $row['common_name'])
    );
    $form['organism_' . $row['organism_id']][$prefix . 'show_genes'] = array(
      '#type' => 'checkbox',
      '#title' => t('Expose genes as an available track for this organism'),
      '#default_value' => variable_get($prefix . 'show_genes', TRUE),
    );
    $form['organism_' . $row['organism_id']][$prefix . 'genes_is_default'] = array(
      '#type' => 'checkbox',
      '#title' => t('Load genes track by default when viewing this organism'),
      '#default_value' => variable_get($prefix . 'genes_is_default', TRUE),
    );
    $form['organism_' . $row['organism_id']][$prefix . 'show_transcripts'] = array(
      '#type' => 'checkbox',
      '#title' => t('Expose transcripts as an available track for this organism'),
      '#default_value' => variable_get($prefix . 'show_transcripts', TRUE),
    );
    $form['organism_' . $row['organism_id']][$prefix . 'transcripts_is_default'] = array(
      '#type' => 'checkbox',
      '#title' => t('Load transcripts track by default when viewing this organism'),
      '#default_value' => variable_get($prefix . 'transcripts_is_default', TRUE),
    );
  }

  return system_settings_form($form);

}
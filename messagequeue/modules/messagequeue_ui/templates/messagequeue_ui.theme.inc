<?php

/**
 * Template preprocessor for theme('messagequeue_pool');
 */
function template_preprocess_messagequeue_pool(&$vars) {
  $path = drupal_get_path('module', 'messagequeue_ui');
  drupal_add_css("{$path}/messagequeue_ui.admin.css");

  $pool = $vars['pool'];

  $vars['machine_name'] = $pool['#machine_name'];
  $vars['name'] = $pool['#name'];
  $vars['brokers'] = drupal_render_children($pool['brokers']);
}

/**
 * Template preprocessor for theme('messagequeue_pool');
 */
function template_preprocess_messagequeue_broker(&$vars) {
  $path = drupal_get_path('module', 'messagequeue_ui');
  drupal_add_css("{$path}/messagequeue_ui.admin.css");

  $broker = $vars['broker'];
  $vars['uri']      = $broker['#uri'];
  $vars['username'] = $broker['#username'];
  $vars['password'] = $broker['#password'];
}

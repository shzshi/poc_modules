<?php
/**
 * @file
 * Admin UI for Message Queue module.
 * Provides an admin page to manage the message queue pools.
 */

/**
 * Admin page.
 */
function messagequeue_ui_manage_pools_page() {
  // Get an array of DrupalMessageQueuePool objects.
  $pools = messagequeue_get_pools();

  $output = array();
  foreach ($pools as $pool) {
    $output[] = array(
      '#type' => 'messagequeue_pool',
      '#pool' => $pool,
    );
  };

  return array(
    '#type' => 'messagequeue_broker',
    '#broker' => current($pools[0]->getBrokers()),
  );

  return $output;
}

/**
 * Form constructor for the message queue pool form.
 *
 * @param optional Object $pool
 * The message queue pool (when editing a pool).
 *
 * @see messagequeue_add_pool_form_validate().
 * @see messagequeue_add_pool_form_submit().
 * @ingroup forms
 */
function messagequeue_ui_pool_form($form, &$form_state, $pool = NULL) {
  // Create a default pool object.
  if (is_null($pool)) {
    $pool = new DrupalMessageQueuePool;
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine Name'),
    '#default_value' => $pool->name,
    '#maxlength' => 128,
  );

  $form['distribution'] = array(
    '#type' => 'radios',
    '#title' => t('Machine Name'),
    '#options' => array(
      MESSAGEQUEUE_DISTRIBUTION_SHARD => t('Shard'),
      MESSAGEQUEUE_DISTRIBUTION_ROUNDROBIN => t('Round robin'),
      MESSAGEQUEUE_DISTRIBUTION_RANDOM => t('Random'),
      MESSAGEQUEUE_DISTRIBUTION_LINEAR => t('Linear'),
    ),
    '#default_value' => $pool->distribution,
    '#maxlength' => 128,
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
}


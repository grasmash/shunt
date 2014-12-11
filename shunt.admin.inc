<?php

/**
 * @file
 * Admin page callback file for the Shunt module.
 */

/**
 * Page callback: Form constructor for the admin settings form.
 *
 * @see shunt_menu()
 * @see shunt_admin_settings_form_submit()
 *
 * @ingroup forms
 */
function shunt_admin_settings_form() {
  $shunts = shunt_get_shunt_definitions();

  // Define table header.
  $header = array(
    'name' => t('Name'),
    'description' => t('Description'),
  );

  // Build table rows.
  $options = array();
  $default_values = array();
  foreach ($shunts as $name => $description) {
    $options[$name] = array(
      'name' => "<strong><label for=\"edit-shunts-{$name}\">{$name}</label></strong>",
      'description' => $description,
    );
    $default_values[$name] = shunt_is_enabled($name);
  }

  // Compile table.
  $form['shunts'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#default_value' => $default_values,
  );

  $form['messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Shunt messages'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['messages']['shunt_message_forms'] = array(
    '#type' => 'textfield',
    '#title' => t('Disabled form'),
    '#default_value' => variable_get('shunt_message_forms', t("We're sorry, this form is currently unavailable.")),
    '#description' => t('When a form is disabled by a shunt, this message will be displayed.'),
  );
  $form['messages']['shunt_message_views'] = array(
    '#type' => 'textfield',
    '#title' => t('Disabled view'),
    '#default_value' => variable_get('shunt_message_views', t("We're sorry, the data for this page is currently unavailable.")),
    '#description' => t('When a view is disabled by a shunt, this message will be displayed.'),
  );
  $form['messages']['shunt_message_services'] = array(
    '#type' => 'textfield',
    '#title' => t('Disabled services resource'),
    '#default_value' => variable_get('shunt_message_services', t("We're sorry. this service is currently unavailable.")),
    '#description' => t('When a services resource is disabled by a shunt, this message will be displayed.'),
  );

  $form['behaviors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default shunt behaviors'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['behaviors']['shunt_behavior_views'] = array(
    '#type' => 'radios',
    '#title' => t('Views shunt behavior'),
    '#default_value' => variable_get('shunt_behavior_views', 'degrade'),
    '#description' => t('Choose the behavior for default the default views shunts.'),
    '#options' => array(
      'degrade' => t('Degrade the view by removing exposed filters'),
      'kill' => t('Kill the view entirely'),
    ),
  );
  $form['behaviors']['shunt_behavior_forms'] = array(
    '#type' => 'radios',
    '#title' => t('Forms shunt behavior'),
    '#default_value' => variable_get('shunt_behavior_forms', 'hide'),
    '#description' => t('Choose the behavior for default the default views shunts.'),
    '#options' => array(
      'hide' => t('Hide the form entirely'),
      'disable' => t('Display the form as disabled'),
    ),
  );

  $form['#submit'][] = 'shunt_admin_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Form submission handler for shunt_admin_settings_form().
 */
function shunt_admin_settings_form_submit($form, &$form_state) {
  _shunt_set_status_multiple($form_state['values']['shunts'], FALSE);
}
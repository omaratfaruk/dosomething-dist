<?php

/**
 * Implements theme_preprocess_html().
 */
function paraneue_dosomething_preprocess_html(&$vars) {
  // Used to print current tagged version in page source
  $vars['ds_version'] = variable_get('ds_version', '[dev]');

  // Checks if current site is an international affiliate
  $vars['is_affiliate'] = dosomething_settings_is_affiliate();
}

/**
 * Implements theme_preprocess_page().
 */
function paraneue_dosomething_preprocess_page(&$vars) {

  // Add theme suggestion for page template based on node.
  if (isset($vars['node']->type)) {
    // If the content type's machine name is "my_machine_name" the file
    // name will be "page--my-machine-name.tpl.php".
    $vars['theme_hook_suggestions'][] = 'page__' . $vars['node']->type;
  }

  /**
   * User Info
   */

  $user_info = user_load($vars['user']->uid);

  if (isset($user_info->field_first_name['und'][0]['safe_value'])) {
    $vars['user_identifier'] = $user_info->field_first_name['und'][0]['safe_value'];
  } else if (isset($user_info->name)) {
    $vars['user_identifier'] = $user_info->name;
  } else {
    $vars['user_identifier'] = $user_info->mail;
  }

  /**
   * Global Main Navigation
   */

  $modifier_classes = '-white -floating';
  if(isset($vars['use_black_navigation']) && $vars['use_black_navigation'] == 1) {
    $modifier_classes = '-floating';
  }

  // Override with environment-specific logo if on staging or local dev:
  $host = $_SERVER['HTTP_HOST'];
  if(strpos($host, 'staging.') !== FALSE) {
    $vars['logo'] = DS_ASSET_PATH . '/images/logo-staging.png';
  }
  else if(strpos($host, 'dev.') !== FALSE) {
    $vars['logo'] = DS_ASSET_PATH . '/images/logo-dev.png';
  }

  $navigation_vars = array(
    'base_path'        => $vars['base_path'],
    'modifier_classes' => $modifier_classes,
    'logo'             => $vars['logo'],
    'front_page'       => $vars['front_page'],
    'logged_in'        => $vars['logged_in'],
    'search_box'       => $vars['search_box'],
    'user_identifier'  => dosomething_helpers_text_truncate($vars['user_identifier'], 8),
    'who_we_are'       => array(
      'text' => theme_get_setting('header_who_we_are_text'),
      'subtext' => theme_get_setting('header_who_we_are_subtext'),
      'link' => theme_get_setting('header_who_we_are_link'),
    ),
    'explore_campaigns'=> array(
      'text' => theme_get_setting('header_explore_campaigns_text'),
      'subtext' => theme_get_setting('header_explore_campaigns_subtext'),
      // 'link' => theme_get_setting('header_explore_campaigns_link'),
    ),
  );

  $vars['navigation'] = theme('navigation', $navigation_vars);

  // Only display tabs for Staff.
  if (isset($vars['tabs']) && !dosomething_user_is_staff()) {
    unset($vars['tabs']);
  }

  /**
   * Determine Page template.
   */
  $full_width = FALSE;
  // Node types to render in the full width page:
  $full_width_types = array(
    'campaign',
    'campaign_group',
    'fact_page',
    'notfound',
    'home',
  );
  if (isset($vars['node']->type) && in_array($vars['node']->type, $full_width_types)) {
    $full_width = TRUE;
  }
  elseif ($vars['theme_hook_suggestions'][0] === 'page__notfound'){
    $full_width = TRUE;
  }
  elseif ($vars['theme_hook_suggestions'][0] === 'page__taxonomy') {
    $full_width = TRUE;
  }
  // Check for User Profile:
  else {
    $is_profile = FALSE;
    if (isset($vars['theme_hook_suggestions'][1])) {
      // Check if page is user/%.
      $is_profile = ($vars['theme_hook_suggestions'][1] === 'page__user__%');
    }
    if ($is_profile) {
      // User profile page does not contain anymore suggestions than
      // 0 => page__user, 1 => page__user__%, and 2=> page__user__[uid].
      if (!isset($vars['theme_hook_suggestions'][3])) {
        // Profile should be full width.
        $full_width = TRUE;
      }
      // Else If this is the Edit Profile page:
      elseif ($vars['theme_hook_suggestions'][3] === 'page__user__edit') {
        // Override the title (which is set to the username by default).
        drupal_set_title(t("Edit Profile"));
      }
    }
  }

  if ($full_width) {
    $vars['theme_hook_suggestions'][] = 'page__full_width';
  }
  else {
    $header_vars = array(
      'title' => drupal_get_title(),
    );
    // If there's a subtitle field on this node, send it to the header
    if (isset($vars['node']->field_subtitle[LANGUAGE_NONE][0]['safe_value'])) {
      $header_vars['subtitle'] = $vars['node']->field_subtitle[LANGUAGE_NONE][0]['safe_value'];
    }
     // Add global header.
    $vars['header'] = theme('header', $header_vars);
  }

  /**
   * Global Page Footer
   */

  $columns = array('first', 'second', 'third');
  $footer_links = array();

  foreach($columns as $column) {
    $prefix = "footer_links_" . $column . "_column_";
    $footer_links[$column] = array();
    $footer_links[$column]['heading'] = theme_get_setting($prefix . "heading");

    $links = explode("\n", trim(theme_get_setting($prefix . "links")));
    $links = array_filter($links); // Remove empty items

    foreach($links as &$link) {
      list($text, $url) = explode('|', $link);
      $link = l(trim($text), trim($url));
    }

    $footer_links[$column]['links'] = $links;
    $footer_links[$column]['class'] = theme_get_setting($prefix . "class");
  }

  // Footer social networks menu.
  $social = paraneue_dosomething_get_social_networks();
  foreach ($social as $id => &$network) {
    $setting_key     = 'footer_social_' . $id;
    $setting_enabled = theme_get_setting($setting_key . '_enabled');
    $setting_url     = theme_get_setting($setting_key . '_url');
    $setting_alt     = theme_get_setting($setting_key . '_alt');

    // Skip disabled and with no URL:
    if (empty($setting_enabled) || empty($setting_enabled)) {
      unset($social[$id]);
      continue;
    }

    // Extend $social array with url and alt text.
    $network['url'] = $setting_url;
    $network['alt'] = t($setting_alt);
  }

  $footer_vars = array(
    'social' => $social,
    'links'  => $footer_links,
    'privacy' => dosomething_user_get_link_privacy_policy(),
    'terms' => dosomething_user_get_link_terms_service(),
  );

  // Footer affiliate logo.
  $footer_logo_enabled = theme_get_setting('footer_affiliate_logo');
  $footer_logo_file    = theme_get_setting('footer_affiliate_logo_file');
  if ($footer_logo_enabled && $footer_logo_file) {
    $file = file_load(theme_get_setting('footer_affiliate_logo_file'));
    if (!empty($file->uri)) {
      $footer_logo = &$footer_vars['affiliate_logo'];
      $footer_logo['file'] = $file->uri;
      $footer_logo['text'] = theme_get_setting('footer_affiliate_logo_text');
    }
  }
  // Render footer.
  $vars['footer'] = theme('footer', $footer_vars);

  /**
   * Search page.
   */
  if (isset($vars['theme_hook_suggestions'][0])) {
    if ($vars['theme_hook_suggestions'][0] == 'page__search' ) {
      // If there are no results.
      if (empty($vars['page']['content']['system_main']['search_results']['search_results']['#results'])) {
        // Set copy.
        $vars['noresults_copy'] = variable_get('dosomething_search_copy_no_results', 'No results found');
        // Recommended campaigns.
        $vars['recommended_campaigns_gallery'] = paraneue_dosomething_get_recommended_campaign_gallery(NULL, NULL, 3);
      }
    }
  }
}


/**
 * Implements theme_preprocess_node().
 */
function paraneue_dosomething_preprocess_node(&$vars) {

  switch($vars['node']->type) {

    case "campaign":
      paraneue_dosomething_preprocess_node_campaign($vars);
      $vars['show_new_reportback'] = theme_get_setting('show_new_reportback');
      break;

    case "campaign_group":
      paraneue_dosomething_preprocess_node_campaign_group($vars);
      paraneue_dosomething_preprocess_field_partners($vars);
      break;

    case "fact_page":
      // Return facts as a chunked array.
      // Allow cta's to be properly embedded in between.
      $vars['facts_chunked'] = array_chunk($vars['facts'], 5);
      break;

    case "home":
      // Set these here to remove db calls from tpl files:
      $vars['show_campaign_finder'] = theme_get_setting('show_campaign_finder');
      $vars['show_sponsors'] = theme_get_setting('show_sponsors');
      break;

    case "static_content":
      // Preprocess field_gallery.
      paraneue_dosomething_preprocess_node_field_gallery($vars);
      break;

    case "notfound":
      paraneue_dosomething_preprocess_node_notfound($vars);
      break;

  }

  // Add $info_bar for all nodes.
  paraneue_dosomething_add_info_bar($vars);
}

/**
 * Preprocesses an info_bar based on given $vars.
 *
 * @see paraneue_dosomething_preprocess_node().
 */
function paraneue_dosomething_add_info_bar(&$vars) {
  // Initialize info_bar_vars with variable that will always be set:
  $zendesk_form_header = t(variable_get('dosomething_zendesk_form_header'));
  $info_bar_vars = array(
    'zendesk_form_header' => $zendesk_form_header,
  );
  // List $vars variable names to pass to info bar:
  $info_var_names = array(
    'formatted_partners',
    'zendesk_form',
  );
  // Loop through the variable names:
  foreach ($info_var_names as $variable) {
    $info_bar_vars[$variable] = NULL;
    // If the vars is set for this variable name:
    if (isset($vars[$variable])) {
      // Store its value.
      $info_bar_vars[$variable] = $vars[$variable];
    }
  }

  $vars['info_bar'] = theme('info_bar', $info_bar_vars);
}

/**
 * Preprocesses a campaign node's $vars.
 *
 * @see paraneue_dosomething_preprocess_node().
 */
function paraneue_dosomething_preprocess_node_campaign(&$vars) {

  // List of partials to add as $vars.
  $partials = array(
    'campaign_creator',
    'campaign_headings',
    'sponsor_logos',
    'promotions',
  );
  // Initialize to NULL.
  foreach ($partials as $partial) {
    $vars[$partial] = NULL;
  }

  // Check for campaign class:
  // @see dosomething_campaign_preprocess_node().
  if (isset($vars['campaign'])) {

    $campaign = $vars['campaign'];

    // Add $campaign_scholarship variable.
    paraneue_dosomething_preprocess_node_campaign_scholarship($vars);

    // Set campaign headings.
    $vars['campaign_headings'] = theme('campaign_headings', $vars);
    // If creator property has been set:
    if ($creator = $campaign->creator) {
      // Pass $campaign->creator array to the campaign_creator theme function.

      $file = file_load($creator['picture']['fid']);
      $creator['picture']['src_square'] = image_style_url('300x300', $file->uri);
      $vars['campaign_creator'] = theme('campaign_creator', $creator);
    }

    // Check for sponsors.
    $vars['sponsor_logos'] = paraneue_dosomething_get_sponsor_logos($campaign->partners);

    // Output sponsors and creator in promotions module.
    if ($vars['sponsor_logos'] || $vars['campaign_creator']) {
      $classes = NULL;

      if ($vars['sponsor_logos'] && $vars['campaign_creator']) {
        $classes = ' -dual';
        $vars['promotions'] = $vars['sponsor_logos'] . $vars['campaign_creator'];
      }
      elseif ($vars['sponsor_logos']) {
        $vars['promotions'] = $vars['sponsor_logos'];
      }
      elseif ($vars['campaign_creator']) {
        $vars['promotions'] = $vars['campaign_creator'];
      }

      $vars['promotions'] = '<div class="promotions' . $classes . '">' . $vars['promotions'] . '</div>';

    }
  }

  // Add class to header if promotions will be included in display.
  if ($vars['promotions']) {
    $vars['classes_array'][] = 'has-promotions';
  }

  // If the campaign requires a signup modal to display:
  if (isset($vars['node']->required_signup_data_form)) {
    // Add JS to open the signup data form modal.
    $id = 'modal-signup-data-form';
    $closeButton = 'false';
    $skipForm = '#dosomething-signup-user-skip-signup-data-form';

    // Add skip button if setting is enabled
    if (isset($vars['node']->skippable_signup_data_form)) {
      $closeButton = 'skip';
    }

    $js = 'require(["neue/modal"], function(Modal) { Modal.open( jQuery("#' . $id . '"), {animated: false, closeButton: "' . $closeButton . '", skipForm: "' . $skipForm . '"}); });';
    drupal_add_js($js, 'inline');
  }

  // If this is not the pitch page:
  if (!isset($vars['is_pitch_page'])) {
    // Set the number of files to display in initial gallery.
    $vars['reportbacks']['initial_count'] = 6;
    // Adds themed Reportback Files.
    paraneue_dosomething_preprocess_reportback_files($vars);
  }

}

/**
 * Adds $gallery_items array of themed Reportback Files for given node preprocess $vars.
 */
function paraneue_dosomething_preprocess_reportback_files(&$vars) {
  $reportbacks_gallery = &$vars['reportbacks_gallery'];

  if (!isset($reportbacks_gallery['initial_count'])) {
    $reportbacks_gallery['initial_count'] = 6;
  }
  $initial_count = $reportbacks_gallery['initial_count'];

  $reportbacks_gallery['items'] = array();
   // Set params to retrieve random promoted Reportback Files for this nid.
  $params = array();
  $params['nid'] = $vars['nid'];
  $params['status'] = 'promoted';
  $params['random'] = TRUE;
  $promoted_results = dosomething_reportback_get_reportback_files_query_result($params, $initial_count);
  foreach ($promoted_results as $rb_file) {
    $rb_file->image = dosomething_image_get_themed_image_url_by_fid($rb_file->fid, '400x400');
    $reportbacks_gallery['items'][] = paraneue_dosomething_get_gallery_item((array) $rb_file, 'photo');
  }

  // Do we have enough promoted items?
  $current_count = count($reportbacks_gallery['items']);
  if ($current_count < $initial_count) {
    // Find out how many additonal approved Reportback items to grab to fulfill the initial count.
    $approved_count = $initial_count - $current_count;
    $reportbacks_gallery['prefetched'] = $approved_count;
    // Set params to retrieve approved Reportback Files for this nid.
    $params['status'] = 'approved';
    unset($params['random']);
    $approved_results  = dosomething_reportback_get_reportback_files_query_result($params, $approved_count);
    foreach ($approved_results as $rb_file) {
      // @todo: DRY. Potentially grab this data from the API endpoint to truly DRY?
      $rb_file->image = dosomething_image_get_themed_image_url_by_fid($rb_file->fid, '300x300');
      $reportbacks_gallery['items'][] = paraneue_dosomething_get_gallery_item((array) $rb_file, 'photo');
    }
  } else {
    $reportbacks_gallery['prefetched'] = 0;
  }

  // Get the total number of approved reportbacks.
  $params['status'] = 'approved';
  if (isset($params['random'])) {
    unset($params['random']);
  }

  $reportbacks_gallery['total'] = dosomething_reportback_get_reportback_files_query_count($params);
}

/**
 * Preprocesses a Campaign Group node.
 *
 * @see paraneue_dosomething_preprocess_node().
 */
function paraneue_dosomething_preprocess_node_campaign_group(&$vars) {
  // Source to append to Campaign Gallery links.
  $source = 'node/' . $vars['nid'];
  $vars['campaign_gallery'] = paraneue_dosomething_get_campaign_gallery($vars['campaigns'], $source);
}

/**
 * Sets a $campaign_scholarship variable based on $vars.
 *
 * @see paraneue_dosomething_preprocess_node().
 */
function paraneue_dosomething_preprocess_node_campaign_scholarship(&$vars) {
  // Initialize to NULL to avoid isset checks in the tpl.
  $vars['campaign_scholarship'] = NULL;
  $vars['prove_scholarship'] = NULL;

  // If a campaign class exists and it has a scholarship:
  if ($vars['campaign'] && $vars['campaign']->scholarship) {
    $campaign = $vars['campaign'];
    $amount = $campaign->scholarship;

    // SMS Game classes:
    if ($campaign->type == 'sms_game') {
      $classes = array('-right');
    }
    // Pitch page classes:
    elseif (isset($campaign->is_pitch_page)) {
      // Values for pitch page:
      $classes = array('-below', '-white',  '-dynamic-right');
    }
    // Else action page classes:
    else {
      // Default classes.
      $classes = array('-above',  '-white');
      // Prove it section classes.
      $prove_classes = array('-below', '-white');
      $vars['prove_scholarship'] = theme('campaign_scholarship', array(
        'amount' => $amount,
        'classes' => $prove_classes,
      ));
    }
    // Default $campaign_scholarship for campaign templates.
    $vars['campaign_scholarship'] = theme('campaign_scholarship', array(
      'amount' => $amount,
      'classes' => $classes,
    ));
  }
}

/**
 * Preprocesses the $vars['galleries'] if exists.
 *
 * @see dosomething_static_content_preprocess_gallery_vars().
 *
 * @param array $vars
 *   Vars passed from a hook_preprocess_node().
 */
function paraneue_dosomething_preprocess_node_field_gallery(&$vars) {

  if (!isset($vars['galleries'])) return;

  // Loop through each gallery:
  foreach ($vars['galleries'] as $delta => &$gallery) {
    // Get the class to apply based on gallery style.
    $gallery_class = paraneue_dosomething_get_gallery_style($gallery['style']);
    // Sets $vars['galleries'][$delta]['class'] to $gallery_class.
    $gallery['class'] = $gallery_class;
    $items_count = count($gallery['items']);
    // Preprocess the $gallery['items'] array.
    for ($i = 0; $i <= $items_count; $i++) {
      // Get class based on the gallery item's sequence.
      $order_class = paraneue_dosomething_get_gallery_item_order_class($i);
      $gallery['items'][$i]['order_class'] = $order_class;
    }
  }

}

/**
 * Preprocesses the field_partners variable, if exists.
 */
function paraneue_dosomething_preprocess_field_partners(&$vars) {
  $vars['partners'] = dosomething_taxonomy_get_partners_data($vars['field_partners']);
  $vars['sponsor_logos'] = paraneue_dosomething_get_sponsor_logos($vars['partners']);
}

/**
 * Implements template_preprocess_taxonomy_term().
 */
function paraneue_dosomething_preprocess_taxonomy_term(&$vars) {
  // Source to append to Campaign Gallery links.
  $source = 'taxonomy/term/' . $vars['tid'];
  $vars['campaign_gallery'] = paraneue_dosomething_get_campaign_gallery($vars['campaigns'], $source, TRUE);

  // Adds sponsor logos.
  paraneue_dosomething_preprocess_field_partners($vars);
  // Adds $partner_info and $formatted_partners variables.
  dosomething_helpers_preprocess_partners_vars($vars);
  if (isset($vars['partner_info'])) {
    $vars['modals'] = theme('modal_links', array('modals' =>
      array(
        'partner_info' => $vars['partner_info'],
        'issue' => $vars['term']->name,
      ),
    ));
  }
  paraneue_dosomething_add_info_bar($vars);
}

/**
 * Preprocesses variables for user profiles.
 *
 * Themes the doing, reportback galleries.
 */
function paraneue_dosomething_preprocess_user_profile(&$vars) {
  global $base_url;
  if ($doing = $vars['doing']) {
    foreach ($doing as $delta => $value) {
      $image = dosomething_image_get_themed_image($value['nid_image'], 'landscape', '400x400');
      $item = array(
        'title' => $value['link'],
        'image' => $image,
        'description' => $value['call_to_action'],
        'url' => $base_url . '/' . $value['path_alias'] . '#prove',
        'button_text' => t("Prove It"),
      );
      $doing_items[$delta] = paraneue_dosomething_get_gallery_item($item, 'figure');
    }
    $vars['doing_gallery'] = paraneue_dosomething_get_gallery($doing_items, 'triad', array(), TRUE);
  }
  // Get an array of reportbacks.
  $reportbacks = $vars['reportbacks'];
  if (!empty($reportbacks)) {
    // Theme each reportback and create an array.
    foreach ($reportbacks as $delta => $rbid) {
      $reportback = reportback_load((int) $rbid);
      $impact = $reportback->quantity . ' ' . $reportback->noun . ' ' . $reportback->verb;
      if (user_access('view any reportback')) {
        // Link to the full reportback entity view.
        $impact = l($impact, 'reportback/' . $rbid);
      }
      $img = dosomething_image_get_themed_image_by_fid($reportback->fids[0], '300x300');
      // Media gallery template expects a full URL.
      $url = $base_url . '/' . drupal_get_path_alias('node/' . $reportback->nid);
      $content = array(
        'link' => $url,
        'title' => $reportback->node_title,
        'image' => $img,
        'impact' => $impact,
      );
      $reportback_items[$delta] = paraneue_dosomething_get_gallery_item($content, 'media');
    }
  }
  // Theme a gallery of reportbacks, and give the user profile template access to it.
  $vars['reportback_gallery'] = paraneue_dosomething_get_gallery($reportback_items, 'duo', array(), TRUE);
}

/**
 * Themes the recommended campaigns for the notfound page
 */
function paraneue_dosomething_preprocess_node_notfound(&$vars) {
  if (isset($vars['raw_search_results']) && count($vars['raw_search_results']) != 0) {
    // Theme the set of results as duo gallery.
    $vars['search_results'] = paraneue_dosomething_get_search_gallery($vars['raw_search_results']);
  }
  else {
    $vars['campaign_results'] = paraneue_dosomething_get_recommended_campaign_gallery(NULL, NULL, 3);
  }
}

/**
 * Preprocesses variables for the search results page.
 */
function paraneue_dosomething_preprocess_search_results(&$vars) {
  if ($search_results = $vars['results']) {
    // Theme the set of results as duo gallery.
    $vars['search_results_gallery'] = paraneue_dosomething_get_search_gallery($search_results);
  }
}

<?php
/**
 * Returns the HTML for Grouped Campaigns page.
 *
 * Available Variables
 * - $nid: Node ID for grouped campaigns page (integer).
 * - $title: Title of grouped campaigns page (string).
 * - $subtitle: Subtitle of grouped campaigns page (string).
 * - $signup_button: Render array for outputting Signup form button (array).
 * - $call_to_action: Call To Action of grouped campaigns page (string).
 * - $scholarship: Scholarship amount (string).
 * - $partners: Array of partners for grouped campaigns (array).
 * - $partner_info: Array of information regarding partners for grouped campaigns (array).
 */
?>

<article id="node-<?php print $node->nid; ?>" class="campaign campaign--grouped <?php print $classes; ?>"<?php print $attributes; ?>>

  <header role="banner" class="-hero">
    <div class="wrapper">
      <h1 class="__title"><?php print $title; ?></h1>
      <?php if (isset($call_to_action)): ?>
      <p class="__subtitle"><?php print $call_to_action; ?></p>
      <?php endif; ?>

      <?php if (isset($end_date)): ?><p class="__date"><?php print $end_date; ?></p><?php endif; ?>

      <?php if (isset($signup_button_primary)): ?>
        <div class="__signup">
          <?php print render($signup_button_primary); ?>
          <?php if (isset($scholarship)): ?>
            <div class="message-callout -below -white -dynamic-right">
              <div class="__copy">
                <p><?php print $scholarship; ?></p>
              </div>
            </div>
          <?php endif; ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($sponsor_logos)): ?>
        <div class="promotions"><?php print $sponsor_logos; ?></div>
      <?php endif; ?>

    </div>
  </header>

  <?php if (isset($intro)): ?>
    <section class="container">
      <div class="wrapper">

        <?php if (isset($intro_image) || isset($intro_video)): ?>
          <div class="container__body <?php if (isset($intro_image) || isset($intro_video)): print '-half"'; else: print '-narrow'; endif; ?>">
            <?php if (isset($intro_title)): ?>
              <h2 class="inline--alt-color"><?php print $intro_title; ?></h2>
            <?php endif; ?>

            <?php print $intro; ?>

            <?php if (isset($modals)): ?>
              <?php print $modals; ?>
            <?php endif; ?>
          </div>


          <?php if (isset($intro_image) || isset($intro_video)): ?>
            <div class="container__body -half">
            <?php if (isset($intro_video)): ?>
              <div class="media-video">
                <?php print $intro_video; ?>
              </div>
            <?php elseif (isset($intro_image)): ?>
              <?php print $intro_image; ?>
            <?php endif; ?>
          <?php endif; ?>
          </div>
        <?php endif; ?>

      </div>
    </section>
  <?php endif; ?>

  <?php if (isset($post_signup_copy)): ?>
    <section class="container">
      <div class="wrapper">
        <div class="container__body -narrow">
          <?php if (isset($post_signup_title)): ?>
            <h2 class="inline--alt-color"><?php print $post_signup_title; ?></h2>
          <?php endif; ?>

          <?php print $post_signup_copy; ?>
        </div>
      </div>
    </section>
  <?php endif; ?>


  <?php if (isset($pre_launch_copy)): ?>
    <section class="container">
      <div class="wrapper">
        <div class="container__body -narrow">
          <?php if (isset($pre_launch_title)): ?>
            <h2 class="inline--alt-color"><?php print $pre_launch_title; ?></h2>
          <?php endif; ?>

          <?php print $pre_launch_copy; ?>
        </div>
      </div>
    </section>
  <?php endif; ?>

  <?php if (!empty($campaign_gallery)): print $campaign_gallery; endif; ?>

  <?php if (!empty($additional_text)): ?>
  <section class="container">
    <div class="wrapper">
      <div class="container__body <?php if (isset($additional_text_image)): print '-half"'; else: print '-narrow'; endif; ?>">
        <?php if (isset($additional_text_title)): ?>
          <h2 class="inline--alt-color"><?php print $additional_text_title; ?></h2>
        <?php endif; ?>

        <?php print $additional_text; ?>
      </div>

      <?php if (isset($additional_text_image)): ?>
        <div class="container__body -half">
          <aside>
            <?php print $additional_text_image; ?>
          </aside>
        </div>
      <?php endif; ?>
    </div>
  </section>
  <?php endif; ?>


  <?php if (!empty($galleries)): ?>
    <section class="container -padded">
      <?php foreach ($galleries as $gallery): ?>
        <div class="wrapper">
          <?php if (isset($gallery['title'])): ?>
            <div class="container__body">
              <h2 class="inline--alt-color"><?php print $gallery['title']; ?></h2>
            </div>
          <?php endif; ?>

          <ul class="gallery -triad">
            <?php foreach ($gallery['items'] as $gallery_item): ?>
              <li class="<?php print $gallery_item['order_class']; ?>">
                <div class="figure">
                  <?php if (isset($gallery_item['image'])): ?>
                    <?php print $gallery_item['image']; ?>
                  <?php endif; ?>

                  <?php if (isset($gallery_item['image_title'])): ?>
                      <h3 class="__title"><?php print $gallery_item['image_title']; ?></h3>
                  <?php endif; ?>
                  <?php if (isset($gallery_item['image_description'])): ?>
                    <div class="__description"><?php print $gallery_item['image_description']; ?></div>
                  <?php endif; ?>
                </div>
              </li>
            <?php endforeach; ?>
          </ul>
        </div>
      <?php endforeach; ?>
    </section>
  <?php endif; ?>

  <?php if (isset($signup_button_secondary)): ?>
    <div class="cta">
      <div class="wrapper">
        <h2 class="__message"><?php print $call_to_action; ?></h2>
        <?php if (isset($signup_button_secondary)): ?>
          <?php print render($signup_button_secondary); ?>
        <?php endif; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($info_bar): ?>
    <?php print $info_bar; ?>
  <?php endif; ?>

</article>

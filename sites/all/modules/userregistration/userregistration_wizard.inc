<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function form_userregistration_wizard($form, &$form_state) {

    // Initialize a description of the steps for the wizard.
    if (empty($form_state['step'])) {
        $form_state['step'] = 1;

        // This array contains the function to be called at each step to get the
        // relevant form elements. It will also store state information for each
        // step.
        $form_state['step_information'] = _form_example_steps();
    }
    $step = &$form_state['step'];
    $stepinfo = $form_state['step_information'][$step]['form'];
    drupal_set_title(t('User Registration:  @step  @stepinfo ', array('@step' => $step, '@stepinfo' => $stepinfo)));

    // Call the function named in $form_state['step_information'] to get the
    // form elements to display for this step.
    $form = $form_state['step_information'][$step]['form']($form, $form_state);

    // Show the 'previous' button if appropriate. Note that #submit is set to
    // a special submit handler, and that we use #limit_validation_errors to
    // skip all complaints about validation when using the back button. The
    // values entered will be discarded, but they will not be validated, which
    // would be annoying in a "back" button.
    if ($step > 1 && $step != 8) {
        $form['prev'] = array(
            '#type' => 'submit',
            '#value' => t('Previous'),
            '#name' => 'prev',
            '#submit' => array('form_userregistration_wizard_previous_submit'),
            '#limit_validation_errors' => array(),
        );
    }
    //drupal_set_message($step);
    // Show the Next button only if there are more steps defined.
    if (($step < count($form_state['step_information'])) && $step != 7) {
        // The Next button should be included on every step
        $form['next'] = array(
            '#type' => 'submit',
            '#value' => t('Next'),
            '#name' => 'next',
            '#submit' => array('form_userregistration_wizard_next_submit'),
        );
    } else {
        // Just in case there are no more steps, we use the default submit handler
        // of the form wizard. Call this button Finish, Submit, or whatever you
        // want to show. When this button is clicked, the
        // form_example_wizard_submit handler will be called.
        if ($step == 7) {
            $form['finish'] = array(
                '#type' => 'submit',
                '#value' => t('Finish'),
                '#name' => 'finish',
                '#submit' => array('form_userregistration_wizard_finish_submit'),
            );
        }
    }

    // Include each validation function defined for the different steps.
    if (function_exists($form_state['step_information'][$step]['form'] . '_validate')) {
        $form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . '_validate');
    }

    return $form;
}

/**
 * Returns the list of steps and their associated forms. This has been separated
 * to clarify and easy the understanding of this example. You should edit this
 * function to include the steps your wizard/multistep form requires.
 *
 * @return $array
 *
 * @ingroup form_example
 */
function _form_example_steps() {
    return array(
        1 => array(
            'form' => 'form_userregistration_wizard_login_info',
        ),
        2 => array(
            'form' => 'form_userregistration_wizard_userdetails_info',
        ),
        3 => array(
            'form' => 'form_userregistration_wizard_car_info',
        ),
        4 => array(
            'form' => 'form_userregistration_wizard_usertype_info',
        ),
        5 => array(
            'form' => 'form_userregistration_wizard_bankdetails_info',
        ),
        6 => array(
            'form' => 'form_userregistration_wizard_intres_info',
        ),
        7 => array(
            'form' => 'form_userregistration_wizard_preview_info',
        ),
        8 => array(
            'form' => 'form_userregistration_wizard_conf_info',
        ),
    );
}

function form_userregistration_wizard_intres_info($form, &$form_state) {
    $form = array();
    $form['Smoker'] = array(
        '#type' => 'select',
        '#title' => t('Smoker'),
        '#default_value' => !empty($form_state['values']['Smoker']) ? $form_state['values']['Smoker'] : 'No',
        '#options' => array(
            'Yes' => 'Yes',
            'No' => 'No',
        ),
    );
    $form['intrest1'] = array(
        '#type' => 'textfield',
        '#title' => t('Intrests while ride'),
        '#default_value' => !empty($form_state['values']['intrest2']) ? $form_state['values']['intrest2'] : '',
    );
    return $form;
}

function form_userregistration_wizard_userdetails_info($form, &$form_state) {
    $form = array();
    $form['first_name'] = array(
        '#type' => 'textfield',
        '#title' => t('First name'),
        '#default_value' => !empty($form_state['values']['first_name']) ? $form_state['values']['first_name'] : '',
        '#size' => 40,
        '#maxlength' => 40
    );
    $form['last_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Last name'),
        '#default_value' => !empty($form_state['values']['last_name']) ? $form_state['values']['last_name'] : '',
        '#size' => 40,
        '#maxlength' => 40
    );
    $form['mobilenumber'] = array(
        '#type' => 'textfield',
        '#title' => t('Mobile'),
        '#default_value' => !empty($form_state['values']['mobilenumber']) ? $form_state['values']['mobilenumber'] : '',
        '#size' => 12,
        '#maxlength' => 12
    );
    $form['alternatenumber'] = array(
        '#type' => 'textfield',
        '#title' => t('Alternate Number'),
        '#default_value' => !empty($form_state['values']['alternatenumber']) ? $form_state['values']['alternatenumber'] : '',
        '#size' => 12,
        '#maxlength' => 12
    );
    $form['dateofbirth'] = array(
        '#title' => t('Date of Birth'),
        '#type' => 'date',
        // '#description' => t('Select your birthdate'),
        '#default_value' => array(
            'month' => format_date(time(), 'custom', 'n'),
            'day' => format_date(time(), 'custom', 'j'),
            'year' => format_date(time(), 'custom', 'Y'),
        ),
    );


    $form['address'] = array(
        '#type' => 'addressfield',
        //   '#required' => TRUE,
        '#title' => t(' Address '),
        '#context' => array('countries' => array('AT', 'AS', 'BE', 'BG', 'CA', 'CY', 'CZ', 'DK', 'EE', 'FI', 'FR', 'DE', 'GR', 'GU', 'HU', 'IE', 'IT', 'LV', 'LT', 'LU', 'MT', 'NL', 'PL', 'PR', 'PT', 'RO', 'SK', 'SI', 'ES', 'SE', 'GB', 'UM', 'US', 'VI', 'IN'), ''),
        '#default_value' => array('country' => 'AU'),
        '#description' => "Please enter your address.",
    );

    $form['drilivnumber'] = array(
        '#type' => 'textfield',
        '#title' => t('Driver Licence Number'),
        '#default_value' => !empty($form_state['values']['drilivnumber']) ? $form_state['values']['drilivnumber'] : '',
        '#size' => 20,
        '#maxlength' => 20
    );
    $form['#tree'] = TRUE;

    $form['documents_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('Upload Documents'),
        // Set up the wrapper so that AJAX will be able to replace the fieldset.
        '#prefix' => '<div id="documents-fieldset-wrapper">',
        '#suffix' => '</div>',
            // '#attributes' => array(
            //                       'style' => 'visibility:hidden;')
    );
    $form['documents_fieldset']['docfile'] = array(
        '#type' => 'file',
        '#title' => t('File path'),
        '#default_value' => !empty($form_state['values']['upload_fieldset']['email']) ? $form_state['values']['upload_fieldset']['email'] : '',
            //     '#size' => 50,
            //   '#maxlength' => 50
    );

    return $form;
}

function form_userregistration_wizard_car_info($form, &$form_state) {

    $form = array();

    $form['cartype'] = array(
        '#type' => 'textfield',
        '#title' => t('Car type'),
        '#default_value' => !empty($form_state['values']['cartype']) ? $form_state['values']['cartype'] : '',
        '#size' => 20,
        '#maxlength' => 20
    );

//    $form['carcapacity'] = array(
//        '#type' => 'textfield',
//        '#title' => t('Car Capacity'),
//        '#default_value' => !empty($form_state['values']['carcapacity']) ? $form_state['values']['carcapacity'] : '',
//    );
    $form['carcapacity'] = array(
        '#type' => 'select',
        '#title' => t('Car Capacity'),
        '#default_value' => !empty($form_state['values']['carcapacity']) ? $form_state['values']['carcapacity'] : '',
        '#options' => array(
            1 => 'One',
            2 => 'Two',
            3 => 'Three',
            4 => 'Four',
            5 => 'Five',
            6 => 'Six',
        ),
            //'#description' => t('Choose an option.'),
    );

    $form['carnumber'] = array(
        '#type' => 'textfield',
        '#title' => t('Car Number'),
        '#default_value' => !empty($form_state['values']['carnumber']) ? $form_state['values']['carnumber'] : '',
        '#size' => 20,
        '#maxlength' => 20
    );

    $form['carcolor'] = array(
        '#type' => 'textfield',
        '#title' => t('Car Color'),
        '#default_value' => !empty($form_state['values']['carcolor']) ? $form_state['values']['carcolor'] : '',
        '#size' => 20,
        '#maxlength' => 20
    );

    return $form;
}

function form_userregistration_wizard_usertype_info($form, &$form_state) {
    $form = array();

    $form['usertype'] = array(
        '#type' => 'radios',
        '#options' => array(
            'passenger' => t('Passenger'),
            'driver' => t('Driver')),
        '#title' => t('User type'),
        '#default_value' => !empty($form_state['values']['usertype']) ? $form_state['values']['usertype'] : '',
    );
    return $form;
}

function form_userregistration_wizard_bankdetails_info($form, &$form_state) {
    $form = array();
//    $form['modeofpayment'] = array(
//        '#type' => 'textfield',
//        '#title' => t('Paymnet mode'),
//        '#default_value' => !empty($form_state['values']['modeofpayment']) ? $form_state['values']['modeofpayment'] : '',
//    );

    $form['#attached']['css'] = array(
        drupal_get_path('module', 'ajax_example') . '/ajax_example.css',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'ajax_example') . '/ajax_example.js',
    );
    $form['modeofpayment'] = array(
        '#type' => 'select',
        '#title' => t('Payment mode'),
        '#default_value' => !empty($form_state['values']['modeofpayment']) ? $form_state['values']['modeofpayment'] : '',
        '#options' => array(
            '*' => t('Select Bank details'),
            'Netbanking' => t('Netbanking'),
            'Paypal' => t('Paypal'),
            'CCDC' => t('Credit/Debit card'),
        ),
        '#ajax' => array(
            'wrapper' => 'modeofpayment-f-s-wrapper',
            'callback' => 'form_userregistration_wizard_bankdetails_info_select_callback',
        ),
            //'#description' => t(' '),
    );


    // The CSS for this module hides this next button if JS is enabled.
    $form['question_type_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Choose'),
        '#attributes' => array('class' => array('next-button')),
        '#limit_validation_errors' => array(), // No need to validate when submitting this.
        '#validate' => array(),
        '#submit' => array('form_userregistration_wizard_choose_submit'),
    );



    // This fieldset just serves as a container for the part of the form
    // that gets rebuilt.
    $form['modeofpayment_f_s'] = array(
        '#type' => 'fieldset',
        // These provide the wrapper referred to in #ajax['wrapper'] above.
        '#title' => 'Details',
        '#prefix' => '<div id="modeofpayment-f-s-wrapper">',
        '#suffix' => '</div>',
    );


    if (!empty($form_state['values']['modeofpayment'])) {

        $selectItem = $form_state['values']['modeofpayment'];

        switch ($selectItem) {
            //'Netbanking' => t('Netbanking'),
            // 'Paypal' => t('Paypal'),
            // 'CCDC' => t('Credit/Debit card'),
            case 'Netbanking' :
                $form['modeofpayment_f_s']['netbankinginfo'] = array(
                    '#markup' => t('You have choosen to pay through Net banking')
                );
                break;
            case 'Paypal' :
                $form['modeofpayment_f_s']['Paypal'] = array(
                    '#type' => 'textfield',
                    '#title' => t('Paypal User name '),
                    '#default_value' => !empty($form_state['values']['Paypal']) ? $form_state['values']['Paypal'] : '',
                );
                break;
            case 'CCDC' :
                $form['modeofpayment_f_s']['CCDC'] = array(
                    '#markup' => t('You have choosen to pay through C or  D card')
                );
                break;
        }
    }


    return $form;
}

function form_userregistration_wizard_preview_info($form, &$form_state) {
    $form = array();
    drupal_set_message('Please check Details');
    // print "<pre>";
    // print_r($form_state);
    // print "</pre>";

    $form = array();

    $form['login_details'] = array(
        '#type' => 'fieldset',
        // These provide the wrapper referred to in #ajax['wrapper'] above.
        '#title' => 'LoginDetails',
        '#prefix' => '<div id="login-wrapper">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );


    $form['login_details']['username'] = array(
        '#type' => 'item',
        '#title' => t('User name'),
        '#markup' => !empty($form_state['step_information'][1]['stored_values']['username']) ? $form_state['step_information'][1]['stored_values']['username'] : 'No data',
    );

    $form['login_details']['email'] = array(
        '#type' => 'item',
        '#title' => t('Email'),
        '#markup' => !empty($form_state['step_information'][1]['stored_values']['email']) ? $form_state['step_information'][1]['stored_values']['email'] : 'No data',
    );


    $form['user_details'] = array(
        '#type' => 'fieldset',
        // These provide the wrapper referred to in #ajax['wrapper'] above.
        '#title' => 'User Details',
        '#prefix' => '<div id="user-details-wrapper">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['user_details']['first_name'] = array(
        '#type' => 'item',
        '#title' => t('First name'),
        '#markup' => !empty($form_state['step_information'][2]['stored_values']['first_name']) ? $form_state['step_information'][2]['stored_values']['first_name'] : 'No data',
    );
    $form['user_details']['last_name'] = array(
        '#type' => 'item',
        '#title' => t('Last name'),
        '#markup' => !empty($form_state['step_information'][2]['stored_values']['last_name']) ? $form_state['step_information'][2]['stored_values']['last_name'] : 'No data',
    );

    $form['user_details']['mobilenumber'] = array(
        '#type' => 'item',
        '#title' => t('Modile'),
        '#markup' => !empty($form_state['step_information'][2]['stored_values']['mobilenumber']) ? $form_state['step_information'][2]['stored_values']['mobilenumber'] : 'No data',
    );

    $form['user_details']['alternatenumber'] = array(
        '#type' => 'item',
        '#title' => t('Alternate number'),
        '#markup' => !empty($form_state['step_information'][2]['stored_values']['alternatenumber']) ? $form_state['step_information'][2]['stored_values']['alternatenumber'] : 'No data',
    );
    $dob = $form_state['step_information'][2]['stored_values']['dateofbirth']['day'] . '/' .
            $form_state['step_information'][2]['stored_values']['dateofbirth']['month'] . '/' .
            $form_state['step_information'][2]['stored_values']['dateofbirth']['year'];
    $form['user_details']['dateofbirth'] = array(
        '#type' => 'item',
        '#title' => t('Date of birth'),
        '#markup' => !empty($dob) ? $dob : 'No data',
    );

    $form['user_details']['drilivnumber'] = array(
        '#type' => 'item',
        '#title' => t('Driver licence number'),
        '#markup' => !empty($form_state['step_information'][2]['stored_values']['drilivnumber']) ? $form_state['step_information'][2]['stored_values']['drilivnumber'] : 'No data',
    );

    $addressFieldData = $form_state['step_information'][2]['stored_values']['address']['country'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['administrative_area'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['sub_administrative_area'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['locality'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['dependent_locality'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['postal_code'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['thoroughfare'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['premise'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['sub_premise'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['organisation_name'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['name_line'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['first_name'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['last_name'] . '/n' .
            $form_state['step_information'][2]['stored_values']['address']['data'] . '/n'
    ;
    $form['user_details']['address'] = array(
        '#type' => 'item',
        '#title' => t('Address'),
        '#markup' => !empty($addressFieldData) ? $addressFieldData : 'No data',
    );

    $form['car_details'] = array(
        '#type' => 'fieldset',
        // These provide the wrapper referred to in #ajax['wrapper'] above.
        '#title' => 'Car Details',
        '#prefix' => '<div id="car-wrapper">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );


    $form['car_details']['username'] = array(
        '#type' => 'item',
        '#title' => t('Car Type'),
        '#markup' => !empty($form_state['step_information'][3]['stored_values']['cartype']) ? $form_state['step_information'][3]['stored_values']['cartype'] : 'No data',
    );

    $form['car_details']['carcapacity'] = array(
        '#type' => 'item',
        '#title' => t('Car capacity'),
        '#markup' => !empty($form_state['step_information'][3]['stored_values']['carcapacity']) ? $form_state['step_information'][3]['stored_values']['carcapacity'] : 'No data',
    );

    $form['car_details']['carnumber'] = array(
        '#type' => 'item',
        '#title' => t('Car number'),
        '#markup' => !empty($form_state['step_information'][3]['stored_values']['carnumber']) ? $form_state['step_information'][3]['stored_values']['carnumber'] : 'No data',
    );
    $form['car_details']['carnumber'] = array(
        '#type' => 'item',
        '#title' => t('Car color'),
        '#markup' => !empty($form_state['step_information'][3]['stored_values']['carcolor']) ? $form_state['step_information'][3]['stored_values']['carcolor'] : 'No data',
    );

    $form['user_type_details'] = array(
        '#type' => 'fieldset',
        // These provide the wrapper referred to in #ajax['wrapper'] above.
        '#title' => 'User type Details',
        '#prefix' => '<div id="user-type-wrapper">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );


    $form['user_type_details']['usertype'] = array(
        '#type' => 'item',
        '#title' => t('User Type'),
        '#markup' => !empty($form_state['step_information'][4]['stored_values']['usertype']) ? $form_state['step_information'][4]['stored_values']['usertype'] : 'No data',
    );

    $form['pay_details'] = array(
        '#type' => 'fieldset',
        // These provide the wrapper referred to in #ajax['wrapper'] above.
        '#title' => 'Payment Details',
        '#prefix' => '<div id="pay-wrapper">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['pay_details']['modeofpayment'] = array(
        '#type' => 'item',
        '#title' => t('Mode of paymnet'),
        '#markup' => !empty($form_state['step_information'][5]['stored_values']['modeofpayment']) ? $form_state['step_information'][5]['stored_values']['modeofpayment'] : 'No data',
    );
    $form['pay_details']['Paypal'] = array(
        '#type' => 'item',
        '#title' => t('A/c type'),
        '#markup' => !empty($form_state['step_information'][5]['stored_values']['Paypal']) ? $form_state['step_information'][5]['stored_values']['Paypal'] : 'No data',
    );
    $form['more_details'] = array(
        '#type' => 'fieldset',
        // These provide the wrapper referred to in #ajax['wrapper'] above.
        '#title' => 'additional details',
        '#prefix' => '<div id="more-details-wrapper">',
        '#suffix' => '</div>',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['more_details']['Smoker'] = array(
        '#type' => 'item',
        '#title' => t('smoker'),
        '#markup' => !empty($form_state['step_information'][6]['stored_values']['Smoker']) ? $form_state['step_information'][6]['stored_values']['Smoker'] : 'No data',
    );

    $form['more_details']['intrest1'] = array(
        '#type' => 'item',
        '#title' => t('Other Intrests'),
        '#markup' => !empty($form_state['step_information'][6]['stored_values']['intrest1']) ? $form_state['step_information'][6]['stored_values']['intrest1'] : 'No data',
    );
      //   print '<pre>';
     // print_r($form_state['step_information'][6]);
     // print '</pre>';
    return $form;
}

function form_userregistration_wizard_login_info($form, &$form_state) {
    $form = array();
    $form['username'] = array(
        '#type' => 'textfield',
        '#title' => t('User name'),
        '#default_value' => !empty($form_state['values']['username']) ? $form_state['values']['username'] : '',
        '#size' => 40,
        '#maxlength' => 20
    );
    $form['password'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#default_value' => !empty($form_state['values']['password']) ? $form_state['values']['password'] : '',
        '#size' => 40,
        '#maxlength' => 20
    );
    $form['confpassword'] = array(
        '#type' => 'password',
        '#title' => t('Confirmation password'),
        '#default_value' => !empty($form_state['values']['confpassword']) ? $form_state['values']['confpassword'] : '',
        '#size' => 40,
        '#maxlength' => 20
    );
    $form['email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#default_value' => !empty($form_state['values']['email']) ? $form_state['values']['email'] : '',
        '#size' => 50,
        '#maxlength' => 50
    );
    return $form;
}

function form_userregistration_wizard_conf_info($form, &$form_state) {

    $form = array();

    $form['confirmation'] = array(
        '#type' => 'fieldset',
        '#title' => t('User Registration Completed'),
        '#prefix' => '<div id="conf-fieldset-wrapper">',
        '#suffix' => '</div>',
    );
    $messa = $form_state['values']['message'];
    if($messa != 'Fail'){
    $form['confirmation']['message'] = array(
        '#markup' => t('Congratulations ... Confirmation mail sent to your mail ' )
        
    );
        $form_state['values']['name'] = $form_state['step_information'][1]['stored_values']['username'];
        $form_state['values']['mail'] = $form_state['step_information'][1]['stored_values']['email'];
        $admin = user_access('administer users');
        $form_state['values']['administer_users']  = $admin;
        
          $form_state['values']['#user'] = drupal_anonymous_user();
          $form_state['values']['#user_category'] = 'register';
          $form_state['values']['#attached']['library'][] = array('system', 'jquery.cookie');
          $form_state['values']['#attributes']['class'][] = 'user-info-from-cookie';

        user_register_submit($form, $form_state);
    }else{
      $form['confirmation']['message'] = array(
        '#markup' => t('Transaction failed . please try againe after some time ' )
    );
      $form_state['values']['message'] = '';
    }
    return $form;
}

//function form_userregistration_wizard_login_info_validate($form, &$form_state) {
//    // validate User name conditions are no special chars allowed
//    $username = $form_state['values']['username'];
//    if (empty($username)) {
//
//        form_set_error('username', t('User name can\'t be blank'));
//    } else {
//        $name_pattern = '/^[a-zA-Z ]*$/';
//        $match_return = preg_match($name_pattern, $username, $name_matches);
//
//        if ($match_return == 0) {
//
//            $msg2_name = "Only alphabets and white space allowed";
//            form_set_error('username', t($msg2_name));
//        }
//    }
//
//    //password validation 
//    $password = $form_state['values']['password'];
//    $confpassword = $form_state['values']['confpassword'];
//    if (empty($password)) {
//        form_set_error('password', t('Password can\'t be blank'));
//    } else if (strlen($password) < 6) {
//
//        form_set_error('password', t('Password must be atleast 6 chars'));
//    } else if (empty($confpassword)) {
//        form_set_error('confpassword', t('Confirmation password can\'t be blank'));
//    } else if ($confpassword != $password) {
//        form_set_error('confpassword', t('Password not match with Confirmation password '));
//    }
//
//    // email validation 
//    $email = $form_state['values']['email'];
//
//    if (empty($email)) {
//        form_set_error('email', t('email can\'t be blank'));
//    } else {
//        $emailPattern = '[\w+-]+(?:\.[\w+-]+)*@[\w+-]+(?:\.[\w+-]+)*(?:\.[a-zA-Z]{2,4})';
//
//        $match_return = preg_match($emailPattern, $email, $email_matches);
//
//        if ($match_return == 0) {
//            $msg2_name = "invalid email";
//            form_set_error('$email', t($msg2_name));
//        }
//    }
//}

function form_userregistration_wizard_upload_submit($form, &$form_state) {
    $current_step = &$form_state['step'];
    $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
    if ($current_step > 1) {
        //$current_step--;
        $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    $form_state['rebuild'] = TRUE;

    drupal_set_message('called');
    //$form
    //return $form;
}

function form_userregistration_wizard_previous_submit($form, &$form_state) {
    $current_step = &$form_state['step'];
    $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
    if ($current_step > 1) {
        $current_step--;
        $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    $form_state['rebuild'] = TRUE;
}

function form_userregistration_wizard_next_submit($form, &$form_state) {
    $current_step = &$form_state['step'];
    $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

    if ($current_step < count($form_state['step_information'])) {
        $current_step++;
        if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
            $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
        } else {
            $form_state['values'] = array();
        }
        $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
        return;
    }
}

function form_userregistration_wizard_finish_submit($form, &$form_state) {

    // address field stored 
    $transaction = db_transaction();
    try{
    $address_fields = array('country', 'administrative_area', 'sub_administrative_area',
        'locality', 'dependent_locality', 'postal_code', 'thoroughfare',
        'premise', 'sub_premise', 'organisation_name', 'name_line',
        'first_name', 'last_name', 'data');

    $user_address_data = array(
        'country' => $form_state['step_information'][2]['stored_values']['address']['country'],
        'administrative_area' => $form_state['step_information'][2]['stored_values']['address']['administrative_area'],
        'sub_administrative_area' => $form_state['step_information'][2]['stored_values']['address']['sub_administrative_area'],
        'locality' => $form_state['step_information'][2]['stored_values']['address']['locality'],
        'dependent_locality' => $form_state['step_information'][2]['stored_values']['address']['dependent_locality'],
        'postal_code' => $form_state['step_information'][2]['stored_values']['address']['postal_code'],
        'thoroughfare' => $form_state['step_information'][2]['stored_values']['address']['thoroughfare'],
        'premise' => $form_state['step_information'][2]['stored_values']['address']['premise'],
        'sub_premise' => $form_state['step_information'][2]['stored_values']['address']['sub_premise'],
        'organisation_name' => $form_state['step_information'][2]['stored_values']['address']['organisation_name'],
        'name_line' => $form_state['step_information'][2]['stored_values']['address']['name_line'],
        'first_name' => $form_state['step_information'][2]['stored_values']['address']['first_name'],
        'last_name' => $form_state['step_information'][2]['stored_values']['address']['last_name'],
        'data' => $form_state['step_information'][2]['stored_values']['address']['data'],
    );

    
    $query = db_insert('useraddress')->fields($address_fields);

    $query->values($user_address_data);

    $result = $query->execute();


    drupal_set_message('registration completed for address' . $result);
    // car details 

    $car_fields = array('carmodel', 'carcapacity', 'carnumber', 'carcolor',);

    $car_data = array(
        'carmodel' => $form_state['step_information'][3]['stored_values']['cartype'],
        'carcapacity' => $form_state['step_information'][3]['stored_values']['carcapacity'],
        'carnumber' => $form_state['step_information'][3]['stored_values']['carnumber'],
        'carcolor' => $form_state['step_information'][3]['stored_values']['carcolor'],
    );

    $car_insert_query = db_insert('cardetails')->fields($car_fields);

    $car_insert_query->values($car_data);

    $car_ins_result = $car_insert_query->execute();
    
    drupal_set_message('car insert  completed for user' . $result);

    // User Details 
    
    $userdetails_fields = array('username', 'password', 'email', 'firstname', 'lastname', 'mobilenumber', 'altmobilenumber', 'dob', 'fileid',
        'driverLicnum', 'docveristatus', 'usertype', 'paymode', 'status', 'useraddressid', 'usercardetailsid');
    
    $dob = str_pad($form_state['step_information'][2]['stored_values']['dateofbirth']['day'], 2, '0', STR_PAD_LEFT) .
            str_pad($form_state['step_information'][2]['stored_values']['dateofbirth']['month'], 2, '0', STR_PAD_LEFT) .
            str_pad($form_state['step_information'][2]['stored_values']['dateofbirth']['year'], 4, '0', STR_PAD_LEFT);
    
    $user_data = array(
            'username' => $form_state['step_information'][1]['stored_values']['username'],
            'password' => $form_state['step_information'][1]['stored_values']['password'],
            'email' => $form_state['step_information'][1]['stored_values']['email'],
            'firstname' => $form_state['step_information'][2]['stored_values']['first_name'],
            'lastname' => $form_state['step_information'][2]['stored_values']['last_name'],
            'mobilenumber' => $form_state['step_information'][2]['stored_values']['mobilenumber'],
            'altmobilenumber' => $form_state['step_information'][2]['stored_values']['alternatenumber'],
            'dob' => intval($dob),
            'fileid' => null,
            'driverLicnum' => $form_state['step_information'][2]['stored_values']['drilivnumber'],
            'docveristatus' => 'pending',
            'usertype' => $form_state['step_information'][4]['stored_values']['usertype'],
            'paymode' => $form_state['step_information'][5]['stored_values']['modeofpayment'],
            'status' => 'NA',
            'useraddressid' => $result,
            'usercardetailsid' => $car_ins_result, 
    );
    
    $user_insert_query = db_insert('userregistration')->fields($userdetails_fields);

    $user_insert_query->values($user_data);

    $user_insert_query->execute();
    
    drupal_set_message('User Inserted');

    //user intrests 
    $intrest_fields = array('intresttext', 'username');
 

    $intrest_data = array(
                    'intresttext' => $form_state['step_information'][6]['stored_values']['intrest1'],
                    'username' => $form_state['step_information'][1]['stored_values']['username']
                     );
    
    $intrest_insert_query = db_insert('intrestes')->fields($intrest_fields);

    $intrest_insert_query->values($intrest_data);

    $intrest_insert_query->execute();
    
    drupal_set_message('User Inserted with intrest details' );
    
    $messa = 'Transaction OK';
    }  catch (Exception $e){
    $transaction ->rollback();
    drupal_set_message('rollback success' );
    watchdog_exception('my_type', $e);
        $messa = 'Fail';
    }
    $current_step = &$form_state['step'];

    $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

    if ($current_step < count($form_state['step_information'])) {
        $current_step++;
        if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
            $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
        } else {
            $form_state['values'] = array();
            $form_state['values']['message'] = $messa ;
        }
        $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
        
        return;
    }
}

/**
 * Callback for the select element.
 *
 * This just selects and returns the questions_fieldset.
 */
function form_userregistration_wizard_bankdetails_info_select_callback($form, $form_state) {
    return $form['modeofpayment_f_s'];
}

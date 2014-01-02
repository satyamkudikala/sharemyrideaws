<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function sharemyride_registration_group_info_form($form, &$form_state) {
    $form['item'] = array(
            '#markup' => t('This is step 2'),
        );
    return $form; 
    
} 
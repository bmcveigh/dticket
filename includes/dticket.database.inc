<?php

/**
 * @file
 * This file includes query functions that get dticket data.
 */

/**
 * This function gets one or many tickets from the dticket table.
 * 
 * @param array $data
 *   This is a key-value array of the query conditions.
 *
 * @return object
 *   This is the result set array of objects resulting in one or
 *   all of the tickets.
 * 
 */
function dticket_get_tickets($data = NULL) {
  $query = db_select('dticket', 'd')
    ->fields('d', array('ticket_id', 'message', 'status', 'submitted'));
  
  if ($data) {
    if (isset($data['ticket_id'])) {
      $query->condition('ticket_id', $data['ticket_id'], '=');
    }
    if (isset($data['uid'])) {
      $query->condition('uid', $data['uid'], '=');
    }
    if (isset($data['last_name'])) {
      $query->condition('last_name', $data['last_name'], '=');
    }
  }
  
  $result = $query->execute()->fetchObject();
  
  return $result;
}

/**
 * Checks the database for the list of all of the existing admins.
 * 
 * @return array
 *    This is the result set array of objects result of all the admins.
 */
function dticket_get_admins() {
  $query = db_select('users', 'u');
  $query->fields('u', array('uid', 'name', 'mail'));
  $query->leftJoin('users_roles', 'ur', 'u.uid=ur.uid');
  $query->leftJoin('role', 'r', 'ur.rid=r.rid');
  $query->condition('r.name', 'administrator', '=');

  $result = $query->execute();

  return $result;
}

/**
 * Gets the ticket status in human-readable format.
 * 
 * @param int $ticket_id
 *   The ticket id to be searched.
 * 
 * @return string
 *   The ticket status for a given ticket id.
 */
function dticket_get_status($ticket_id) {
  $query = db_select('dticket', 'dt');
  $query->join('dticket_status', 'dts', 'dt.status=dts.id');
  $query->fields('dts', array('status'));
  $result = $query->execute()->fetchColumn();
  
  return $result;
}

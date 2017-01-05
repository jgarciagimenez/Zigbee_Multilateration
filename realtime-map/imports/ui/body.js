
import { Template } from 'meteor/templating';

import { Coordinates } from '../api/coordenadas.js';

import './body.html';
import './coordenada.js';

Template.body.helpers({
  coordenadas() {
    return Coordinates.find({}, { sort: { createdAt: -1 } });
  },
  lastcoor: function() {
    return Coordinates.find({}, {sort: {DateTime: -1, limit: 1,}}) ;
  },
});


Template.body.events({
  'submit .new-task'(event) {
    // Prevent default browser form submit
    event.preventDefault();

    // Get value from form element
    const target = event.target;
    const text = target.text.value;

    // Insert coordinates
    Coordinates.insert({
      text,
      createdAt: new Date(), // current time
    });

    // Clear form
    target.text.value = '';
  },
});

function myMove() {
  var element;
  window.alert('asldkjfalskdjfal');
  var pos = 10;
  var dest = Coordinates.find({}, {sort: {DateTime: -1, limit: 1,}});
  dest = dest.text;
  element = document.getElementById("animate");
  var id = setInterval(frame, 5);

  function frame(){
    if (pos == number(dest)){
      clearInterval(id);
    }
    else{
      pos++;
      element.style.top = pos + 'px';
      element.style.left = pos + 'px';
  }
}
}

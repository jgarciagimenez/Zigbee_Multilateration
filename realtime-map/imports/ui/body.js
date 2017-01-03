import './body.html';
import './coordenada.js';

Template.body.helpers({
  coordenadas() {
    const instance = Template.instance();

    return Coordinates.find({}, { sort: { createdAt: -1 } });
  },
});

Template.body.onCreated(function bodyOnCreated() {
  this.state = new ReactiveDict();
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

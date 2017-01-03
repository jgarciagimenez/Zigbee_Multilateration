
import { Template } from 'meteor/templating';

import { Coordinates } from '../api/coordenadas.js';

import './coordenada.html';

Template.coordenada.events({

  'click .delete'() {
    Coordinates.remove(this._id);
  },
});

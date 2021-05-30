<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Game extends Model
{
    protected $fillable = ['gamen', 'player1', 'player2', 'channel'];
}

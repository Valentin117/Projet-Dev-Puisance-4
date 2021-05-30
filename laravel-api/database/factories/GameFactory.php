<?php

/** @var \Illuminate\Database\Eloquent\Factory $factory */

use App\Game;
use Faker\Generator as Faker;

$factory->define(Game::class, function (Faker $faker) {
    return [
        'gamen' => $faker->sentence(6, true),
        'player1' => $faker->sentence(1, true),
        'player2'=> $faker->sentence(1, true),
        'channel' => $faker->paragraph(3, true)
    ];
});

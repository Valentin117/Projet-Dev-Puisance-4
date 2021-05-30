<?php

namespace App\Http\Resources;

use Illuminate\Http\Resources\Json\JsonResource;

class Game extends JsonResource
{
    /**
     * Transform the resource into an array.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return array
     */
    public function toArray($request)
    {
        return [
            'gamen' => 'Numero de la Game : ' . $this->gamen,
            'player1' => 'Joueur 1 : ' . $this->player1,
            'player2' => 'Joueur 2 : ' . $this->player2,
            'channel' => substr($this->channel, 0, 30) . '...'
        ];
    }
}

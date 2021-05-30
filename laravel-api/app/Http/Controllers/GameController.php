<?php

namespace App\Http\Controllers;

use App\Http\Resources\Game as ResourcesGame;
use App\Game;
use Illuminate\Http\Request;

class GameController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $games = ResourcesGame::collection(Game::orderByDesc('created_at')->get());

        return $games->toJson(JSON_PRETTY_PRINT);
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        if(Game::create($request->all())){
            return response()->json([
               'success' => 'Game ajouté avec succés'
            ]);
        };
    }

    /**
     * Display the specified resource.
     *
     * @param  \App\Game  $game
     * @return \Illuminate\Http\Response
     */
    public function show(Game $game)
    {
        return new ResourcesGame($game);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \App\Game  $game
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, Game $game)
    {
        
        if($game->update($request->all())){
            return response()->json([
               'success' => 'Game modifiée avec succés'
            ]);
        };
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  \App\Game  $game
     * @return \Illuminate\Http\Response
     */
    public function destroy(Game $game)
    {
        if($game->delete()){
            return response()->json([
               'success' => 'Game supprimé avec succés'
            ]);
        };
    }
}

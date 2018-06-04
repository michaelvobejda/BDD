'use strict';

var BDDapp = angular.module('BDDapp', ['ngRoute']);

BDDapp.config(['$routeProvider', 
    function($routeProvider) {
        $routeProvider
        .when('/', {
            templateUrl: '/components/board/board-template.html',
            controller: 'BoardController',
        })
        .otherwise({
            redirectTo: '/',
        });
    }]);


BDDapp.controller('MainController', ['$scope', 
    function($scope) {
        
    }]);
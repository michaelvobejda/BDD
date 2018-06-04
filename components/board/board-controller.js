'use strict';

BDDapp.controller('BoardController', ['$scope', 
    function($scope) {

        $scope.getSizeOptions = [1, 2, 3, 4, 5, 6, 7, 8, 9];

        $scope.size = 3;

        $scope.getSize = function() {
            return new Array($scope.size);
        };

        $scope.updateBoard = function() {
            $scope.$apply();
        }
        
    }]);
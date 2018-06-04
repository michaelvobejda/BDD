'use strict';

BDDapp.controller('BoardController', ['$scope', 
    function($scope) {

        $scope.sizeOptions = [1, 2, 3, 4, 5];

        $scope.size = $scope.sizeOptions[2];

        $scope.getSize = function() {
            return new Array($scope.size);
        };

        $scope.updateBoard = function(newSize) {
            $scope.size = newSize;
        }
        
    }]);
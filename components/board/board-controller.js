'use strict';

// var jquery = require('jquery');

BDDapp.controller('BoardController', ['$scope', '$http',
    function($scope, $http) {

        $scope.sizeOptions = [1, 2, 3, 4, 5];

        $scope.size = $scope.sizeOptions[2];

        $scope.boardArr = new Array(Math.pow($scope.size, 4));

        $scope.boardString = "";

        $scope.getSize = function() {
            var arr = [];
            for (var i = 0; i < $scope.size; i++) {
                arr.push(i);
            }
            return arr;
        };

        $scope.getId = function(w, x, y, z) {
            var s = $scope.size;
            return s * s * (s * w + y) + s * x + z;
        }

        $scope.currSpace;

        $scope.selectedElement;

        $scope.spaceClicked = function(event) {
            event.target.value = "";
            if ($scope.selectedElement === event.target) { // deselecting
                $scope.selectedElement.style.backgroundColor = "";
                $scope.selectedElement = undefined;
            } else { // selecting new space
                if ($scope.selectedElement) {
                    $scope.selectedElement.style.backgroundColor = "";
                }
                $scope.selectedElement = event.target;

                event.target.style.backgroundColor = 'lightgreen';
                event.target.innerHTML = "";
            }
        }

        $scope.spaceChanged = function(object) {
            // update board
            var id = $scope.selectedElement.id;
            var value = $scope.selectedElement.value;
            $scope.boardArr[id] = value;
            var numRegex = /[0-9]|\./;
            if(!numRegex.test(value)) {
                console.log(value);
                $scope.selectedElement.style.backgroundColor = 'lightcoral';
            } else {
                $scope.selectedElement.style.backgroundColor = "";
            }

            // deselect updated space
            $scope.selectedElement.blur();
            $scope.selectedElement = undefined;
        }

        $scope.updateBoard = function(newSize) {
            $scope.size = newSize;
        }


        $scope.boardToString = function() {
            var str = '';
            for (var i = 0; i < Math.pow($scope.size, 4); i++) {
                if (!$scope.boardArr[i]) {
                    str += '.';
                } else {
                    str += $scope.boardArr[i];
                }
                if ((i + 1) % Math.pow($scope.size, 2) === 0) {
                    str += '|';
                }
            }
            console.log(str);
            return str;
        }

        function sleep(ms) {
            return new Promise(resolve => setTimeout(resolve, ms));
        }

        // 825471396|194326578|376985241|519743862|632598417|487612935|263159784|948267153|751834629
        $scope.loadBoard = async function(boardString) {
            var space;
            var str = boardString.replace(/\|/g, "");

            if (!str || str.length !== Math.pow($scope.size, 4)) {
                console.log('Input string incorrect length.');
                return;
            }

            for (var i = 0; i < $scope.boardArr.length; i++) {
                space = document.getElementById(i);
                if (str[i] !== '.' && str[i] !== space.value) {
                    $scope.boardArr[i] = str[i];
                    space.style.backgroundColor = "lightgreen";
                    space.value = str[i];
                    await sleep(100);
                    space.style.backgroundColor = "";
                }

            }
        }

        $scope.solve = function() {
            var board = $scope.boardToString();
            // $http.get('http://localhost:3000/python_eda').success(function(response) {
            //     console.log('response:')
            //     console.log(response);
            //     $scope.loadBoard(response)
            // });
            console.log('boardString')
            // console.log(boardString)

            $http({
                method: 'POST',
                url: 'http://127.0.0.1:5000/', 
                data: board,
                // params: {
                //     board: board,
                // }
            }).then(function successCallback(response) {
                // this callback will be called asynchronously
                // when the response is available
                console.log('response:')
                console.log(response);
                $scope.loadBoard(response)
                }, function errorCallback(response) {
                  // called asynchronously if an error occurs
                  // or server returns response with an error status.
                  console.log('error:')
                  console.log(response);
                });
            // $.ajax({
            //     type: "POST",
            //     url: "localhost:3000/python_eda",
            //     data: { param: boardString },
            //     success: function(response) {
            //         console.log('response:')
            //         console.log(response);
            //         $scope.loadBoard(response)
            //     }
            // });
        }
        
    }]);
/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
$(document).ready(function() {

    $(".click-title").mouseenter( function(    e){
        e.preventDefault();
        this.style.cursor="pointer";
    });
    $(".click-title").mousedown( function(event){
        event.preventDefault();
    });

    // Ugly code while this script is shared among several pages
    try{
        refreshHitsPerSecond(true);
    } catch(e){}
    try{
        refreshResponseTimeOverTime(true);
    } catch(e){}
    try{
        refreshResponseTimePercentiles();
    } catch(e){}
});


var responseTimePercentilesInfos = {
        data: {"result": {"minY": 7.0, "minX": 0.0, "maxY": 195.0, "series": [{"data": [[0.0, 7.0], [0.1, 7.0], [0.2, 7.0], [0.3, 8.0], [0.4, 8.0], [0.5, 8.0], [0.6, 8.0], [0.7, 8.0], [0.8, 8.0], [0.9, 8.0], [1.0, 8.0], [1.1, 8.0], [1.2, 8.0], [1.3, 8.0], [1.4, 8.0], [1.5, 8.0], [1.6, 8.0], [1.7, 8.0], [1.8, 8.0], [1.9, 8.0], [2.0, 8.0], [2.1, 8.0], [2.2, 8.0], [2.3, 8.0], [2.4, 8.0], [2.5, 8.0], [2.6, 8.0], [2.7, 8.0], [2.8, 8.0], [2.9, 8.0], [3.0, 8.0], [3.1, 8.0], [3.2, 8.0], [3.3, 8.0], [3.4, 8.0], [3.5, 8.0], [3.6, 8.0], [3.7, 8.0], [3.8, 8.0], [3.9, 8.0], [4.0, 8.0], [4.1, 8.0], [4.2, 8.0], [4.3, 8.0], [4.4, 8.0], [4.5, 8.0], [4.6, 8.0], [4.7, 8.0], [4.8, 8.0], [4.9, 8.0], [5.0, 8.0], [5.1, 8.0], [5.2, 8.0], [5.3, 8.0], [5.4, 8.0], [5.5, 8.0], [5.6, 8.0], [5.7, 8.0], [5.8, 8.0], [5.9, 8.0], [6.0, 8.0], [6.1, 8.0], [6.2, 8.0], [6.3, 8.0], [6.4, 8.0], [6.5, 8.0], [6.6, 8.0], [6.7, 8.0], [6.8, 8.0], [6.9, 8.0], [7.0, 8.0], [7.1, 8.0], [7.2, 8.0], [7.3, 8.0], [7.4, 8.0], [7.5, 8.0], [7.6, 8.0], [7.7, 8.0], [7.8, 8.0], [7.9, 8.0], [8.0, 8.0], [8.1, 8.0], [8.2, 8.0], [8.3, 8.0], [8.4, 8.0], [8.5, 8.0], [8.6, 8.0], [8.7, 8.0], [8.8, 8.0], [8.9, 8.0], [9.0, 8.0], [9.1, 8.0], [9.2, 8.0], [9.3, 8.0], [9.4, 8.0], [9.5, 8.0], [9.6, 8.0], [9.7, 8.0], [9.8, 8.0], [9.9, 8.0], [10.0, 8.0], [10.1, 8.0], [10.2, 8.0], [10.3, 8.0], [10.4, 8.0], [10.5, 8.0], [10.6, 8.0], [10.7, 8.0], [10.8, 8.0], [10.9, 8.0], [11.0, 8.0], [11.1, 8.0], [11.2, 8.0], [11.3, 8.0], [11.4, 8.0], [11.5, 8.0], [11.6, 8.0], [11.7, 8.0], [11.8, 8.0], [11.9, 8.0], [12.0, 8.0], [12.1, 8.0], [12.2, 8.0], [12.3, 8.0], [12.4, 8.0], [12.5, 8.0], [12.6, 8.0], [12.7, 8.0], [12.8, 8.0], [12.9, 8.0], [13.0, 8.0], [13.1, 8.0], [13.2, 8.0], [13.3, 8.0], [13.4, 8.0], [13.5, 8.0], [13.6, 8.0], [13.7, 8.0], [13.8, 8.0], [13.9, 8.0], [14.0, 8.0], [14.1, 8.0], [14.2, 8.0], [14.3, 8.0], [14.4, 8.0], [14.5, 8.0], [14.6, 8.0], [14.7, 8.0], [14.8, 8.0], [14.9, 8.0], [15.0, 8.0], [15.1, 8.0], [15.2, 8.0], [15.3, 8.0], [15.4, 8.0], [15.5, 9.0], [15.6, 9.0], [15.7, 9.0], [15.8, 9.0], [15.9, 9.0], [16.0, 9.0], [16.1, 9.0], [16.2, 9.0], [16.3, 9.0], [16.4, 9.0], [16.5, 9.0], [16.6, 9.0], [16.7, 9.0], [16.8, 9.0], [16.9, 9.0], [17.0, 9.0], [17.1, 9.0], [17.2, 9.0], [17.3, 9.0], [17.4, 9.0], [17.5, 9.0], [17.6, 9.0], [17.7, 9.0], [17.8, 9.0], [17.9, 9.0], [18.0, 9.0], [18.1, 9.0], [18.2, 9.0], [18.3, 9.0], [18.4, 9.0], [18.5, 9.0], [18.6, 9.0], [18.7, 9.0], [18.8, 9.0], [18.9, 9.0], [19.0, 9.0], [19.1, 9.0], [19.2, 9.0], [19.3, 9.0], [19.4, 9.0], [19.5, 9.0], [19.6, 9.0], [19.7, 9.0], [19.8, 9.0], [19.9, 9.0], [20.0, 9.0], [20.1, 9.0], [20.2, 9.0], [20.3, 9.0], [20.4, 9.0], [20.5, 9.0], [20.6, 9.0], [20.7, 9.0], [20.8, 9.0], [20.9, 9.0], [21.0, 9.0], [21.1, 9.0], [21.2, 9.0], [21.3, 9.0], [21.4, 9.0], [21.5, 9.0], [21.6, 9.0], [21.7, 9.0], [21.8, 9.0], [21.9, 9.0], [22.0, 9.0], [22.1, 9.0], [22.2, 9.0], [22.3, 9.0], [22.4, 9.0], [22.5, 9.0], [22.6, 9.0], [22.7, 9.0], [22.8, 9.0], [22.9, 9.0], [23.0, 9.0], [23.1, 9.0], [23.2, 9.0], [23.3, 9.0], [23.4, 9.0], [23.5, 9.0], [23.6, 9.0], [23.7, 9.0], [23.8, 9.0], [23.9, 9.0], [24.0, 9.0], [24.1, 9.0], [24.2, 9.0], [24.3, 9.0], [24.4, 9.0], [24.5, 9.0], [24.6, 9.0], [24.7, 9.0], [24.8, 9.0], [24.9, 9.0], [25.0, 9.0], [25.1, 9.0], [25.2, 9.0], [25.3, 9.0], [25.4, 9.0], [25.5, 9.0], [25.6, 9.0], [25.7, 9.0], [25.8, 9.0], [25.9, 9.0], [26.0, 9.0], [26.1, 9.0], [26.2, 9.0], [26.3, 9.0], [26.4, 9.0], [26.5, 9.0], [26.6, 9.0], [26.7, 9.0], [26.8, 9.0], [26.9, 9.0], [27.0, 9.0], [27.1, 9.0], [27.2, 9.0], [27.3, 9.0], [27.4, 9.0], [27.5, 9.0], [27.6, 9.0], [27.7, 9.0], [27.8, 9.0], [27.9, 9.0], [28.0, 9.0], [28.1, 9.0], [28.2, 9.0], [28.3, 9.0], [28.4, 9.0], [28.5, 9.0], [28.6, 9.0], [28.7, 9.0], [28.8, 9.0], [28.9, 9.0], [29.0, 9.0], [29.1, 9.0], [29.2, 9.0], [29.3, 9.0], [29.4, 9.0], [29.5, 9.0], [29.6, 9.0], [29.7, 9.0], [29.8, 9.0], [29.9, 9.0], [30.0, 9.0], [30.1, 9.0], [30.2, 9.0], [30.3, 9.0], [30.4, 9.0], [30.5, 9.0], [30.6, 9.0], [30.7, 9.0], [30.8, 9.0], [30.9, 9.0], [31.0, 9.0], [31.1, 9.0], [31.2, 9.0], [31.3, 9.0], [31.4, 9.0], [31.5, 9.0], [31.6, 9.0], [31.7, 9.0], [31.8, 9.0], [31.9, 9.0], [32.0, 9.0], [32.1, 9.0], [32.2, 9.0], [32.3, 9.0], [32.4, 9.0], [32.5, 9.0], [32.6, 9.0], [32.7, 9.0], [32.8, 9.0], [32.9, 9.0], [33.0, 9.0], [33.1, 9.0], [33.2, 9.0], [33.3, 9.0], [33.4, 9.0], [33.5, 9.0], [33.6, 9.0], [33.7, 9.0], [33.8, 9.0], [33.9, 9.0], [34.0, 9.0], [34.1, 9.0], [34.2, 9.0], [34.3, 9.0], [34.4, 9.0], [34.5, 9.0], [34.6, 9.0], [34.7, 9.0], [34.8, 9.0], [34.9, 9.0], [35.0, 9.0], [35.1, 9.0], [35.2, 9.0], [35.3, 9.0], [35.4, 9.0], [35.5, 9.0], [35.6, 9.0], [35.7, 9.0], [35.8, 9.0], [35.9, 9.0], [36.0, 9.0], [36.1, 9.0], [36.2, 9.0], [36.3, 9.0], [36.4, 9.0], [36.5, 9.0], [36.6, 9.0], [36.7, 9.0], [36.8, 9.0], [36.9, 9.0], [37.0, 9.0], [37.1, 9.0], [37.2, 9.0], [37.3, 9.0], [37.4, 9.0], [37.5, 9.0], [37.6, 9.0], [37.7, 9.0], [37.8, 9.0], [37.9, 9.0], [38.0, 9.0], [38.1, 9.0], [38.2, 9.0], [38.3, 9.0], [38.4, 9.0], [38.5, 9.0], [38.6, 9.0], [38.7, 9.0], [38.8, 9.0], [38.9, 9.0], [39.0, 9.0], [39.1, 9.0], [39.2, 9.0], [39.3, 9.0], [39.4, 9.0], [39.5, 9.0], [39.6, 9.0], [39.7, 9.0], [39.8, 9.0], [39.9, 9.0], [40.0, 9.0], [40.1, 9.0], [40.2, 9.0], [40.3, 9.0], [40.4, 9.0], [40.5, 9.0], [40.6, 9.0], [40.7, 10.0], [40.8, 10.0], [40.9, 10.0], [41.0, 10.0], [41.1, 10.0], [41.2, 10.0], [41.3, 10.0], [41.4, 10.0], [41.5, 10.0], [41.6, 10.0], [41.7, 10.0], [41.8, 10.0], [41.9, 10.0], [42.0, 10.0], [42.1, 10.0], [42.2, 10.0], [42.3, 10.0], [42.4, 10.0], [42.5, 10.0], [42.6, 10.0], [42.7, 10.0], [42.8, 10.0], [42.9, 10.0], [43.0, 10.0], [43.1, 10.0], [43.2, 10.0], [43.3, 10.0], [43.4, 10.0], [43.5, 10.0], [43.6, 10.0], [43.7, 10.0], [43.8, 10.0], [43.9, 10.0], [44.0, 10.0], [44.1, 10.0], [44.2, 10.0], [44.3, 10.0], [44.4, 10.0], [44.5, 10.0], [44.6, 10.0], [44.7, 10.0], [44.8, 10.0], [44.9, 10.0], [45.0, 10.0], [45.1, 10.0], [45.2, 10.0], [45.3, 10.0], [45.4, 10.0], [45.5, 10.0], [45.6, 10.0], [45.7, 10.0], [45.8, 10.0], [45.9, 10.0], [46.0, 10.0], [46.1, 10.0], [46.2, 10.0], [46.3, 10.0], [46.4, 10.0], [46.5, 10.0], [46.6, 10.0], [46.7, 10.0], [46.8, 10.0], [46.9, 10.0], [47.0, 10.0], [47.1, 10.0], [47.2, 10.0], [47.3, 10.0], [47.4, 10.0], [47.5, 10.0], [47.6, 10.0], [47.7, 10.0], [47.8, 10.0], [47.9, 10.0], [48.0, 10.0], [48.1, 10.0], [48.2, 10.0], [48.3, 10.0], [48.4, 10.0], [48.5, 10.0], [48.6, 10.0], [48.7, 10.0], [48.8, 10.0], [48.9, 10.0], [49.0, 10.0], [49.1, 10.0], [49.2, 10.0], [49.3, 10.0], [49.4, 10.0], [49.5, 10.0], [49.6, 10.0], [49.7, 10.0], [49.8, 10.0], [49.9, 10.0], [50.0, 10.0], [50.1, 10.0], [50.2, 10.0], [50.3, 10.0], [50.4, 10.0], [50.5, 10.0], [50.6, 10.0], [50.7, 10.0], [50.8, 10.0], [50.9, 10.0], [51.0, 10.0], [51.1, 10.0], [51.2, 10.0], [51.3, 10.0], [51.4, 10.0], [51.5, 10.0], [51.6, 10.0], [51.7, 10.0], [51.8, 10.0], [51.9, 10.0], [52.0, 10.0], [52.1, 10.0], [52.2, 10.0], [52.3, 10.0], [52.4, 10.0], [52.5, 10.0], [52.6, 10.0], [52.7, 10.0], [52.8, 10.0], [52.9, 10.0], [53.0, 10.0], [53.1, 10.0], [53.2, 10.0], [53.3, 10.0], [53.4, 10.0], [53.5, 10.0], [53.6, 10.0], [53.7, 10.0], [53.8, 10.0], [53.9, 10.0], [54.0, 10.0], [54.1, 10.0], [54.2, 10.0], [54.3, 10.0], [54.4, 10.0], [54.5, 10.0], [54.6, 10.0], [54.7, 10.0], [54.8, 10.0], [54.9, 10.0], [55.0, 10.0], [55.1, 10.0], [55.2, 10.0], [55.3, 10.0], [55.4, 10.0], [55.5, 10.0], [55.6, 10.0], [55.7, 10.0], [55.8, 10.0], [55.9, 10.0], [56.0, 10.0], [56.1, 10.0], [56.2, 10.0], [56.3, 10.0], [56.4, 10.0], [56.5, 10.0], [56.6, 10.0], [56.7, 10.0], [56.8, 10.0], [56.9, 10.0], [57.0, 10.0], [57.1, 10.0], [57.2, 10.0], [57.3, 10.0], [57.4, 10.0], [57.5, 10.0], [57.6, 10.0], [57.7, 10.0], [57.8, 10.0], [57.9, 10.0], [58.0, 10.0], [58.1, 10.0], [58.2, 10.0], [58.3, 10.0], [58.4, 10.0], [58.5, 10.0], [58.6, 10.0], [58.7, 10.0], [58.8, 10.0], [58.9, 10.0], [59.0, 10.0], [59.1, 10.0], [59.2, 10.0], [59.3, 10.0], [59.4, 10.0], [59.5, 10.0], [59.6, 10.0], [59.7, 10.0], [59.8, 10.0], [59.9, 10.0], [60.0, 10.0], [60.1, 10.0], [60.2, 10.0], [60.3, 10.0], [60.4, 10.0], [60.5, 10.0], [60.6, 10.0], [60.7, 10.0], [60.8, 10.0], [60.9, 10.0], [61.0, 10.0], [61.1, 10.0], [61.2, 10.0], [61.3, 10.0], [61.4, 10.0], [61.5, 10.0], [61.6, 11.0], [61.7, 11.0], [61.8, 11.0], [61.9, 11.0], [62.0, 11.0], [62.1, 11.0], [62.2, 11.0], [62.3, 11.0], [62.4, 11.0], [62.5, 11.0], [62.6, 11.0], [62.7, 11.0], [62.8, 11.0], [62.9, 11.0], [63.0, 11.0], [63.1, 11.0], [63.2, 11.0], [63.3, 11.0], [63.4, 11.0], [63.5, 11.0], [63.6, 11.0], [63.7, 11.0], [63.8, 11.0], [63.9, 11.0], [64.0, 11.0], [64.1, 11.0], [64.2, 11.0], [64.3, 11.0], [64.4, 11.0], [64.5, 11.0], [64.6, 11.0], [64.7, 11.0], [64.8, 11.0], [64.9, 11.0], [65.0, 11.0], [65.1, 11.0], [65.2, 11.0], [65.3, 11.0], [65.4, 11.0], [65.5, 11.0], [65.6, 11.0], [65.7, 11.0], [65.8, 11.0], [65.9, 11.0], [66.0, 11.0], [66.1, 11.0], [66.2, 11.0], [66.3, 11.0], [66.4, 11.0], [66.5, 11.0], [66.6, 11.0], [66.7, 11.0], [66.8, 11.0], [66.9, 11.0], [67.0, 11.0], [67.1, 11.0], [67.2, 11.0], [67.3, 11.0], [67.4, 11.0], [67.5, 11.0], [67.6, 11.0], [67.7, 11.0], [67.8, 11.0], [67.9, 11.0], [68.0, 11.0], [68.1, 11.0], [68.2, 11.0], [68.3, 11.0], [68.4, 11.0], [68.5, 11.0], [68.6, 11.0], [68.7, 11.0], [68.8, 11.0], [68.9, 11.0], [69.0, 11.0], [69.1, 11.0], [69.2, 11.0], [69.3, 11.0], [69.4, 11.0], [69.5, 11.0], [69.6, 11.0], [69.7, 11.0], [69.8, 11.0], [69.9, 11.0], [70.0, 11.0], [70.1, 11.0], [70.2, 11.0], [70.3, 11.0], [70.4, 11.0], [70.5, 11.0], [70.6, 11.0], [70.7, 11.0], [70.8, 11.0], [70.9, 11.0], [71.0, 11.0], [71.1, 11.0], [71.2, 11.0], [71.3, 11.0], [71.4, 11.0], [71.5, 11.0], [71.6, 11.0], [71.7, 11.0], [71.8, 11.0], [71.9, 11.0], [72.0, 11.0], [72.1, 11.0], [72.2, 11.0], [72.3, 11.0], [72.4, 11.0], [72.5, 11.0], [72.6, 11.0], [72.7, 11.0], [72.8, 11.0], [72.9, 11.0], [73.0, 11.0], [73.1, 11.0], [73.2, 11.0], [73.3, 11.0], [73.4, 11.0], [73.5, 11.0], [73.6, 11.0], [73.7, 11.0], [73.8, 11.0], [73.9, 11.0], [74.0, 11.0], [74.1, 11.0], [74.2, 11.0], [74.3, 11.0], [74.4, 11.0], [74.5, 11.0], [74.6, 11.0], [74.7, 11.0], [74.8, 11.0], [74.9, 11.0], [75.0, 11.0], [75.1, 11.0], [75.2, 11.0], [75.3, 11.0], [75.4, 11.0], [75.5, 11.0], [75.6, 11.0], [75.7, 11.0], [75.8, 11.0], [75.9, 11.0], [76.0, 11.0], [76.1, 11.0], [76.2, 11.0], [76.3, 11.0], [76.4, 11.0], [76.5, 11.0], [76.6, 11.0], [76.7, 11.0], [76.8, 11.0], [76.9, 11.0], [77.0, 11.0], [77.1, 11.0], [77.2, 11.0], [77.3, 11.0], [77.4, 11.0], [77.5, 11.0], [77.6, 11.0], [77.7, 11.0], [77.8, 11.0], [77.9, 11.0], [78.0, 11.0], [78.1, 11.0], [78.2, 11.0], [78.3, 11.0], [78.4, 11.0], [78.5, 11.0], [78.6, 11.0], [78.7, 11.0], [78.8, 11.0], [78.9, 11.0], [79.0, 11.0], [79.1, 11.0], [79.2, 11.0], [79.3, 11.0], [79.4, 11.0], [79.5, 11.0], [79.6, 11.0], [79.7, 11.0], [79.8, 11.0], [79.9, 11.0], [80.0, 11.0], [80.1, 11.0], [80.2, 11.0], [80.3, 11.0], [80.4, 11.0], [80.5, 11.0], [80.6, 11.0], [80.7, 11.0], [80.8, 11.0], [80.9, 11.0], [81.0, 11.0], [81.1, 11.0], [81.2, 11.0], [81.3, 11.0], [81.4, 11.0], [81.5, 11.0], [81.6, 11.0], [81.7, 11.0], [81.8, 11.0], [81.9, 11.0], [82.0, 11.0], [82.1, 11.0], [82.2, 11.0], [82.3, 11.0], [82.4, 11.0], [82.5, 11.0], [82.6, 11.0], [82.7, 11.0], [82.8, 11.0], [82.9, 11.0], [83.0, 11.0], [83.1, 11.0], [83.2, 11.0], [83.3, 11.0], [83.4, 11.0], [83.5, 11.0], [83.6, 11.0], [83.7, 11.0], [83.8, 11.0], [83.9, 11.0], [84.0, 11.0], [84.1, 11.0], [84.2, 11.0], [84.3, 11.0], [84.4, 11.0], [84.5, 11.0], [84.6, 11.0], [84.7, 11.0], [84.8, 11.0], [84.9, 11.0], [85.0, 11.0], [85.1, 11.0], [85.2, 11.0], [85.3, 11.0], [85.4, 11.0], [85.5, 11.0], [85.6, 11.0], [85.7, 11.0], [85.8, 11.0], [85.9, 11.0], [86.0, 11.0], [86.1, 11.0], [86.2, 11.0], [86.3, 11.0], [86.4, 11.0], [86.5, 11.0], [86.6, 11.0], [86.7, 11.0], [86.8, 11.0], [86.9, 12.0], [87.0, 12.0], [87.1, 12.0], [87.2, 12.0], [87.3, 12.0], [87.4, 12.0], [87.5, 12.0], [87.6, 12.0], [87.7, 12.0], [87.8, 12.0], [87.9, 12.0], [88.0, 12.0], [88.1, 12.0], [88.2, 12.0], [88.3, 12.0], [88.4, 12.0], [88.5, 12.0], [88.6, 12.0], [88.7, 12.0], [88.8, 12.0], [88.9, 12.0], [89.0, 12.0], [89.1, 12.0], [89.2, 12.0], [89.3, 12.0], [89.4, 12.0], [89.5, 12.0], [89.6, 12.0], [89.7, 12.0], [89.8, 12.0], [89.9, 12.0], [90.0, 12.0], [90.1, 12.0], [90.2, 12.0], [90.3, 12.0], [90.4, 12.0], [90.5, 12.0], [90.6, 12.0], [90.7, 12.0], [90.8, 12.0], [90.9, 12.0], [91.0, 12.0], [91.1, 12.0], [91.2, 12.0], [91.3, 12.0], [91.4, 12.0], [91.5, 12.0], [91.6, 13.0], [91.7, 13.0], [91.8, 13.0], [91.9, 13.0], [92.0, 13.0], [92.1, 13.0], [92.2, 13.0], [92.3, 13.0], [92.4, 13.0], [92.5, 13.0], [92.6, 13.0], [92.7, 13.0], [92.8, 13.0], [92.9, 13.0], [93.0, 13.0], [93.1, 13.0], [93.2, 13.0], [93.3, 14.0], [93.4, 14.0], [93.5, 14.0], [93.6, 14.0], [93.7, 14.0], [93.8, 14.0], [93.9, 15.0], [94.0, 15.0], [94.1, 15.0], [94.2, 16.0], [94.3, 17.0], [94.4, 17.0], [94.5, 17.0], [94.6, 19.0], [94.7, 19.0], [94.8, 20.0], [94.9, 20.0], [95.0, 21.0], [95.1, 22.0], [95.2, 22.0], [95.3, 23.0], [95.4, 24.0], [95.5, 26.0], [95.6, 26.0], [95.7, 28.0], [95.8, 29.0], [95.9, 32.0], [96.0, 32.0], [96.1, 52.0], [96.2, 66.0], [96.3, 71.0], [96.4, 75.0], [96.5, 78.0], [96.6, 79.0], [96.7, 87.0], [96.8, 91.0], [96.9, 93.0], [97.0, 93.0], [97.1, 94.0], [97.2, 97.0], [97.3, 100.0], [97.4, 102.0], [97.5, 106.0], [97.6, 108.0], [97.7, 111.0], [97.8, 114.0], [97.9, 116.0], [98.0, 119.0], [98.1, 122.0], [98.2, 123.0], [98.3, 123.0], [98.4, 124.0], [98.5, 126.0], [98.6, 128.0], [98.7, 132.0], [98.8, 134.0], [98.9, 139.0], [99.0, 140.0], [99.1, 145.0], [99.2, 149.0], [99.3, 153.0], [99.4, 159.0], [99.5, 164.0], [99.6, 170.0], [99.7, 176.0], [99.8, 177.0], [99.9, 179.0], [100.0, 195.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 100.0, "title": "Response Time Percentiles"}},
        getOptions: function() {
            return {
                series: {
                    points: { show: false }
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimePercentiles'
                },
                xaxis: {
                    tickDecimals: 1,
                    axisLabel: "Percentiles",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Percentile value in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : %x.2 percentile was %y ms"
                },
                selection: { mode: "xy" },
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimePercentiles"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimesPercentiles"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimesPercentiles"), dataset, prepareOverviewOptions(options));
        }
};

/**
 * @param elementId Id of element where we display message
 */
function setEmptyGraph(elementId) {
    $(function() {
        $(elementId).text("No graph series with filter="+seriesFilter);
    });
}

// Response times percentiles
function refreshResponseTimePercentiles() {
    var infos = responseTimePercentilesInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimePercentiles");
        return;
    }
    if (isGraph($("#flotResponseTimesPercentiles"))){
        infos.createGraph();
    } else {
        var choiceContainer = $("#choicesResponseTimePercentiles");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimesPercentiles", "#overviewResponseTimesPercentiles");
        $('#bodyResponseTimePercentiles .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var responseTimeDistributionInfos = {
        data: {"result": {"minY": 49.0, "minX": 0.0, "maxY": 1751.0, "series": [{"data": [[0.0, 1751.0], [100.0, 49.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 100, "maxX": 100.0, "title": "Response Time Distribution"}},
        getOptions: function() {
            var granularity = this.data.result.granularity;
            return {
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimeDistribution'
                },
                xaxis:{
                    axisLabel: "Response times in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of responses",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                bars : {
                    show: true,
                    barWidth: this.data.result.granularity
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: function(label, xval, yval, flotItem){
                        return yval + " responses for " + label + " were between " + xval + " and " + (xval + granularity) + " ms";
                    }
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimeDistribution"), prepareData(data.result.series, $("#choicesResponseTimeDistribution")), options);
        }

};

// Response time distribution
function refreshResponseTimeDistribution() {
    var infos = responseTimeDistributionInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimeDistribution");
        return;
    }
    if (isGraph($("#flotResponseTimeDistribution"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimeDistribution");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        $('#footerResponseTimeDistribution .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var syntheticResponseTimeDistributionInfos = {
        data: {"result": {"minY": 1800.0, "minX": 0.0, "ticks": [[0, "Requests having \nresponse time <= 500ms"], [1, "Requests having \nresponse time > 500ms and <= 1,500ms"], [2, "Requests having \nresponse time > 1,500ms"], [3, "Requests in error"]], "maxY": 1800.0, "series": [{"data": [[0.0, 1800.0]], "color": "#9ACD32", "isOverall": false, "label": "Requests having \nresponse time <= 500ms", "isController": false}, {"data": [], "color": "yellow", "isOverall": false, "label": "Requests having \nresponse time > 500ms and <= 1,500ms", "isController": false}, {"data": [], "color": "orange", "isOverall": false, "label": "Requests having \nresponse time > 1,500ms", "isController": false}, {"data": [], "color": "#FF6347", "isOverall": false, "label": "Requests in error", "isController": false}], "supportsControllersDiscrimination": false, "maxX": 4.9E-324, "title": "Synthetic Response Times Distribution"}},
        getOptions: function() {
            return {
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendSyntheticResponseTimeDistribution'
                },
                xaxis:{
                    axisLabel: "Response times ranges",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                    tickLength:0,
                    min:-0.5,
                    max:3.5
                },
                yaxis: {
                    axisLabel: "Number of responses",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                bars : {
                    show: true,
                    align: "center",
                    barWidth: 0.25,
                    fill:.75
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: function(label, xval, yval, flotItem){
                        return yval + " " + label;
                    }
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var options = this.getOptions();
            prepareOptions(options, data);
            options.xaxis.ticks = data.result.ticks;
            $.plot($("#flotSyntheticResponseTimeDistribution"), prepareData(data.result.series, $("#choicesSyntheticResponseTimeDistribution")), options);
        }

};

// Response time distribution
function refreshSyntheticResponseTimeDistribution() {
    var infos = syntheticResponseTimeDistributionInfos;
    prepareSeries(infos.data, true);
    if (isGraph($("#flotSyntheticResponseTimeDistribution"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesSyntheticResponseTimeDistribution");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        $('#footerSyntheticResponseTimeDistribution .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var activeThreadsOverTimeInfos = {
        data: {"result": {"minY": 2.1385542168674676, "minX": 1.763685241E12, "maxY": 40.079601990049795, "series": [{"data": [[1.763685245E12, 2.191616766467066], [1.763685244E12, 2.2168674698795177], [1.763685243E12, 2.2035928143712575], [1.763685248E12, 2.1445783132530103], [1.763685247E12, 2.1845238095238093], [1.763685246E12, 2.1506024096385548], [1.76368525E12, 2.2215568862275443], [1.763685249E12, 2.1385542168674676], [1.763685242E12, 2.3630952380952372], [1.763685241E12, 40.079601990049795], [1.763685251E12, 2.214285714285715]], "isOverall": false, "label": "线程组", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.763685251E12, "title": "Active Threads Over Time"}},
        getOptions: function() {
            return {
                series: {
                    stack: true,
                    lines: {
                        show: true,
                        fill: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of active threads",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 6,
                    show: true,
                    container: '#legendActiveThreadsOverTime'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                selection: {
                    mode: 'xy'
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : At %x there were %y active threads"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesActiveThreadsOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotActiveThreadsOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewActiveThreadsOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Active Threads Over Time
function refreshActiveThreadsOverTime(fixTimestamps) {
    var infos = activeThreadsOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotActiveThreadsOverTime"))) {
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesActiveThreadsOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotActiveThreadsOverTime", "#overviewActiveThreadsOverTime");
        $('#footerActiveThreadsOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var timeVsThreadsInfos = {
        data: {"result": {"minY": 9.4375, "minX": 1.0, "maxY": 135.125, "series": [{"data": [[2.0, 9.540971168437016], [35.0, 15.0], [34.0, 16.5], [49.0, 23.0], [3.0, 11.118902439024394], [60.0, 15.5], [4.0, 12.818181818181818], [71.0, 91.2], [69.0, 67.33333333333333], [70.0, 14.0], [72.0, 108.37499999999999], [75.0, 104.28571428571429], [77.0, 101.16666666666666], [78.0, 100.0], [79.0, 101.0], [76.0, 53.25], [80.0, 104.66666666666667], [81.0, 116.625], [82.0, 129.5], [83.0, 135.125], [5.0, 13.142857142857142], [85.0, 73.0], [87.0, 112.4], [86.0, 77.0], [89.0, 89.5], [91.0, 17.0], [88.0, 91.625], [90.0, 20.5], [92.0, 19.0], [6.0, 12.25], [13.0, 17.0], [1.0, 9.4375], [31.0, 26.0]], "isOverall": false, "label": "Products", "isController": false}, {"data": [[6.432222222222232, 14.447777777777807]], "isOverall": false, "label": "Products-Aggregated", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 92.0, "title": "Time VS Threads"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    axisLabel: "Number of active threads",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response times in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: { noColumns: 2,show: true, container: '#legendTimeVsThreads' },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s: At %x.2 active threads, Average response time was %y.2 ms"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesTimeVsThreads"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotTimesVsThreads"), dataset, options);
            // setup overview
            $.plot($("#overviewTimesVsThreads"), dataset, prepareOverviewOptions(options));
        }
};

// Time vs threads
function refreshTimeVsThreads(){
    var infos = timeVsThreadsInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyTimeVsThreads");
        return;
    }
    if(isGraph($("#flotTimesVsThreads"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTimeVsThreads");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTimesVsThreads", "#overviewTimesVsThreads");
        $('#footerTimeVsThreads .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var bytesThroughputOverTimeInfos = {
        data : {"result": {"minY": 24598.0, "minX": 1.763685241E12, "maxY": 312609.0, "series": [{"data": [[1.763685245E12, 263014.0], [1.763685244E12, 261302.0], [1.763685243E12, 246229.0], [1.763685248E12, 248585.0], [1.763685247E12, 256478.0], [1.763685246E12, 263947.0], [1.76368525E12, 262784.0], [1.763685249E12, 250633.0], [1.763685242E12, 259392.0], [1.763685241E12, 312609.0], [1.763685251E12, 158094.0]], "isOverall": false, "label": "Bytes received per second", "isController": false}, {"data": [[1.763685245E12, 41917.0], [1.763685244E12, 41666.0], [1.763685243E12, 41917.0], [1.763685248E12, 41666.0], [1.763685247E12, 42168.0], [1.763685246E12, 41666.0], [1.76368525E12, 41917.0], [1.763685249E12, 41666.0], [1.763685242E12, 42168.0], [1.763685241E12, 50451.0], [1.763685251E12, 24598.0]], "isOverall": false, "label": "Bytes sent per second", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.763685251E12, "title": "Bytes Throughput Over Time"}},
        getOptions : function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity) ,
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Bytes / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendBytesThroughputOverTime'
                },
                selection: {
                    mode: "xy"
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y"
                }
            };
        },
        createGraph : function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesBytesThroughputOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotBytesThroughputOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewBytesThroughputOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Bytes throughput Over Time
function refreshBytesThroughputOverTime(fixTimestamps) {
    var infos = bytesThroughputOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotBytesThroughputOverTime"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesBytesThroughputOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotBytesThroughputOverTime", "#overviewBytesThroughputOverTime");
        $('#footerBytesThroughputOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var responseTimesOverTimeInfos = {
        data: {"result": {"minY": 9.6566265060241, "minX": 1.763685241E12, "maxY": 51.238805970149265, "series": [{"data": [[1.763685245E12, 9.73053892215569], [1.763685244E12, 9.783132530120481], [1.763685243E12, 9.844311377245507], [1.763685248E12, 9.6566265060241], [1.763685247E12, 9.857142857142858], [1.763685246E12, 9.83132530120482], [1.76368525E12, 9.940119760479044], [1.763685249E12, 9.66265060240963], [1.763685242E12, 10.166666666666673], [1.763685241E12, 51.238805970149265], [1.763685251E12, 9.704081632653063]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.763685251E12, "title": "Response Time Over Time"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average response time was %y ms"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Response Times Over Time
function refreshResponseTimeOverTime(fixTimestamps) {
    var infos = responseTimesOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimeOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotResponseTimesOverTime"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimesOverTime", "#overviewResponseTimesOverTime");
        $('#footerResponseTimesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var latenciesOverTimeInfos = {
        data: {"result": {"minY": 9.620481927710847, "minX": 1.763685241E12, "maxY": 51.129353233830834, "series": [{"data": [[1.763685245E12, 9.640718562874246], [1.763685244E12, 9.759036144578316], [1.763685243E12, 9.778443113772449], [1.763685248E12, 9.620481927710847], [1.763685247E12, 9.815476190476186], [1.763685246E12, 9.813253012048184], [1.76368525E12, 9.904191616766465], [1.763685249E12, 9.632530120481926], [1.763685242E12, 10.10119047619048], [1.763685241E12, 51.129353233830834], [1.763685251E12, 9.673469387755098]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.763685251E12, "title": "Latencies Over Time"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response latencies in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendLatenciesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average latency was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesLatenciesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotLatenciesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewLatenciesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Latencies Over Time
function refreshLatenciesOverTime(fixTimestamps) {
    var infos = latenciesOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyLatenciesOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotLatenciesOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesLatenciesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotLatenciesOverTime", "#overviewLatenciesOverTime");
        $('#footerLatenciesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var connectTimeOverTimeInfos = {
        data: {"result": {"minY": 3.928143712574849, "minX": 1.763685241E12, "maxY": 20.67661691542288, "series": [{"data": [[1.763685245E12, 4.005988023952096], [1.763685244E12, 3.9638554216867457], [1.763685243E12, 3.928143712574849], [1.763685248E12, 4.042168674698794], [1.763685247E12, 4.101190476190475], [1.763685246E12, 4.0180722891566285], [1.76368525E12, 4.11377245508982], [1.763685249E12, 4.060240963855422], [1.763685242E12, 4.172619047619048], [1.763685241E12, 20.67661691542288], [1.763685251E12, 3.9591836734693877]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.763685251E12, "title": "Connect Time Over Time"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getConnectTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average Connect Time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendConnectTimeOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average connect time was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesConnectTimeOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotConnectTimeOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewConnectTimeOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Connect Time Over Time
function refreshConnectTimeOverTime(fixTimestamps) {
    var infos = connectTimeOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyConnectTimeOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotConnectTimeOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesConnectTimeOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotConnectTimeOverTime", "#overviewConnectTimeOverTime");
        $('#footerConnectTimeOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var responseTimePercentilesOverTimeInfos = {
        data: {"result": {"minY": 7.0, "minX": 1.763685241E12, "maxY": 195.0, "series": [{"data": [[1.763685245E12, 20.0], [1.763685244E12, 13.0], [1.763685243E12, 23.0], [1.763685248E12, 13.0], [1.763685247E12, 19.0], [1.763685246E12, 15.0], [1.76368525E12, 21.0], [1.763685249E12, 13.0], [1.763685242E12, 32.0], [1.763685241E12, 195.0], [1.763685251E12, 12.0]], "isOverall": false, "label": "Max", "isController": false}, {"data": [[1.763685245E12, 11.0], [1.763685244E12, 11.0], [1.763685243E12, 11.0], [1.763685248E12, 11.0], [1.763685247E12, 11.0], [1.763685246E12, 11.0], [1.76368525E12, 11.0], [1.763685249E12, 11.0], [1.763685242E12, 12.0], [1.763685241E12, 138.40000000000003], [1.763685251E12, 11.0]], "isOverall": false, "label": "90th percentile", "isController": false}, {"data": [[1.763685245E12, 15.239999999999952], [1.763685244E12, 13.0], [1.763685243E12, 20.279999999999973], [1.763685248E12, 12.330000000000013], [1.763685247E12, 14.170000000000016], [1.763685246E12, 13.660000000000025], [1.76368525E12, 18.279999999999973], [1.763685249E12, 13.0], [1.763685242E12, 19.58000000000004], [1.763685241E12, 178.95999999999998], [1.763685251E12, 12.0]], "isOverall": false, "label": "99th percentile", "isController": false}, {"data": [[1.763685245E12, 12.0], [1.763685244E12, 11.650000000000006], [1.763685243E12, 12.0], [1.763685248E12, 11.650000000000006], [1.763685247E12, 11.0], [1.763685246E12, 11.0], [1.76368525E12, 11.0], [1.763685249E12, 11.0], [1.763685242E12, 12.0], [1.763685241E12, 163.4999999999999], [1.763685251E12, 12.0]], "isOverall": false, "label": "95th percentile", "isController": false}, {"data": [[1.763685245E12, 8.0], [1.763685244E12, 7.0], [1.763685243E12, 8.0], [1.763685248E12, 7.0], [1.763685247E12, 7.0], [1.763685246E12, 8.0], [1.76368525E12, 7.0], [1.763685249E12, 8.0], [1.763685242E12, 8.0], [1.763685241E12, 9.0], [1.763685251E12, 8.0]], "isOverall": false, "label": "Min", "isController": false}, {"data": [[1.763685245E12, 10.0], [1.763685244E12, 10.0], [1.763685243E12, 10.0], [1.763685248E12, 10.0], [1.763685247E12, 10.0], [1.763685246E12, 10.0], [1.76368525E12, 10.0], [1.763685249E12, 10.0], [1.763685242E12, 10.0], [1.763685241E12, 15.0], [1.763685251E12, 10.0]], "isOverall": false, "label": "Median", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.763685251E12, "title": "Response Time Percentiles Over Time (successful requests only)"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true,
                        fill: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Response Time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimePercentilesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Response time was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimePercentilesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimePercentilesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimePercentilesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Response Time Percentiles Over Time
function refreshResponseTimePercentilesOverTime(fixTimestamps) {
    var infos = responseTimePercentilesOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotResponseTimePercentilesOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesResponseTimePercentilesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimePercentilesOverTime", "#overviewResponseTimePercentilesOverTime");
        $('#footerResponseTimePercentilesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var responseTimeVsRequestInfos = {
    data: {"result": {"minY": 10.0, "minX": 98.0, "maxY": 15.0, "series": [{"data": [[167.0, 10.0], [166.0, 10.0], [168.0, 10.0], [98.0, 10.0], [201.0, 15.0]], "isOverall": false, "label": "Successes", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 201.0, "title": "Response Time Vs Request"}},
    getOptions: function() {
        return {
            series: {
                lines: {
                    show: false
                },
                points: {
                    show: true
                }
            },
            xaxis: {
                axisLabel: "Global number of requests per second",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            yaxis: {
                axisLabel: "Median Response Time in ms",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            legend: {
                noColumns: 2,
                show: true,
                container: '#legendResponseTimeVsRequest'
            },
            selection: {
                mode: 'xy'
            },
            grid: {
                hoverable: true // IMPORTANT! this is needed for tooltip to work
            },
            tooltip: true,
            tooltipOpts: {
                content: "%s : Median response time at %x req/s was %y ms"
            },
            colors: ["#9ACD32", "#FF6347"]
        };
    },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesResponseTimeVsRequest"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotResponseTimeVsRequest"), dataset, options);
        // setup overview
        $.plot($("#overviewResponseTimeVsRequest"), dataset, prepareOverviewOptions(options));

    }
};

// Response Time vs Request
function refreshResponseTimeVsRequest() {
    var infos = responseTimeVsRequestInfos;
    prepareSeries(infos.data);
    if (isGraph($("#flotResponseTimeVsRequest"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimeVsRequest");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimeVsRequest", "#overviewResponseTimeVsRequest");
        $('#footerResponseRimeVsRequest .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var latenciesVsRequestInfos = {
    data: {"result": {"minY": 10.0, "minX": 98.0, "maxY": 15.0, "series": [{"data": [[167.0, 10.0], [166.0, 10.0], [168.0, 10.0], [98.0, 10.0], [201.0, 15.0]], "isOverall": false, "label": "Successes", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 201.0, "title": "Latencies Vs Request"}},
    getOptions: function() {
        return{
            series: {
                lines: {
                    show: false
                },
                points: {
                    show: true
                }
            },
            xaxis: {
                axisLabel: "Global number of requests per second",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            yaxis: {
                axisLabel: "Median Latency in ms",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            legend: { noColumns: 2,show: true, container: '#legendLatencyVsRequest' },
            selection: {
                mode: 'xy'
            },
            grid: {
                hoverable: true // IMPORTANT! this is needed for tooltip to work
            },
            tooltip: true,
            tooltipOpts: {
                content: "%s : Median Latency time at %x req/s was %y ms"
            },
            colors: ["#9ACD32", "#FF6347"]
        };
    },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesLatencyVsRequest"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotLatenciesVsRequest"), dataset, options);
        // setup overview
        $.plot($("#overviewLatenciesVsRequest"), dataset, prepareOverviewOptions(options));
    }
};

// Latencies vs Request
function refreshLatenciesVsRequest() {
        var infos = latenciesVsRequestInfos;
        prepareSeries(infos.data);
        if(isGraph($("#flotLatenciesVsRequest"))){
            infos.createGraph();
        }else{
            var choiceContainer = $("#choicesLatencyVsRequest");
            createLegend(choiceContainer, infos);
            infos.createGraph();
            setGraphZoomable("#flotLatenciesVsRequest", "#overviewLatenciesVsRequest");
            $('#footerLatenciesVsRequest .legendColorBox > div').each(function(i){
                $(this).clone().prependTo(choiceContainer.find("li").eq(i));
            });
        }
};

var hitsPerSecondInfos = {
        data: {"result": {"minY": 96.0, "minX": 1.763685241E12, "maxY": 204.0, "series": [{"data": [[1.763685245E12, 167.0], [1.763685244E12, 167.0], [1.763685243E12, 166.0], [1.763685248E12, 167.0], [1.763685247E12, 167.0], [1.763685246E12, 166.0], [1.76368525E12, 167.0], [1.763685249E12, 166.0], [1.763685242E12, 167.0], [1.763685241E12, 204.0], [1.763685251E12, 96.0]], "isOverall": false, "label": "hitsPerSecond", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.763685251E12, "title": "Hits Per Second"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of hits / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendHitsPerSecond"
                },
                selection: {
                    mode : 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y.2 hits/sec"
                }
            };
        },
        createGraph: function createGraph() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesHitsPerSecond"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotHitsPerSecond"), dataset, options);
            // setup overview
            $.plot($("#overviewHitsPerSecond"), dataset, prepareOverviewOptions(options));
        }
};

// Hits per second
function refreshHitsPerSecond(fixTimestamps) {
    var infos = hitsPerSecondInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if (isGraph($("#flotHitsPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesHitsPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotHitsPerSecond", "#overviewHitsPerSecond");
        $('#footerHitsPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var codesPerSecondInfos = {
        data: {"result": {"minY": 98.0, "minX": 1.763685241E12, "maxY": 201.0, "series": [{"data": [[1.763685245E12, 167.0], [1.763685244E12, 166.0], [1.763685243E12, 167.0], [1.763685248E12, 166.0], [1.763685247E12, 168.0], [1.763685246E12, 166.0], [1.76368525E12, 167.0], [1.763685249E12, 166.0], [1.763685242E12, 168.0], [1.763685241E12, 201.0], [1.763685251E12, 98.0]], "isOverall": false, "label": "200", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.763685251E12, "title": "Codes Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of responses / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendCodesPerSecond"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "Number of Response Codes %s at %x was %y.2 responses / sec"
                }
            };
        },
    createGraph: function() {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesCodesPerSecond"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotCodesPerSecond"), dataset, options);
        // setup overview
        $.plot($("#overviewCodesPerSecond"), dataset, prepareOverviewOptions(options));
    }
};

// Codes per second
function refreshCodesPerSecond(fixTimestamps) {
    var infos = codesPerSecondInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotCodesPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesCodesPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotCodesPerSecond", "#overviewCodesPerSecond");
        $('#footerCodesPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var transactionsPerSecondInfos = {
        data: {"result": {"minY": 98.0, "minX": 1.763685241E12, "maxY": 201.0, "series": [{"data": [[1.763685245E12, 167.0], [1.763685244E12, 166.0], [1.763685243E12, 167.0], [1.763685248E12, 166.0], [1.763685247E12, 168.0], [1.763685246E12, 166.0], [1.76368525E12, 167.0], [1.763685249E12, 166.0], [1.763685242E12, 168.0], [1.763685241E12, 201.0], [1.763685251E12, 98.0]], "isOverall": false, "label": "Products-success", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.763685251E12, "title": "Transactions Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of transactions / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendTransactionsPerSecond"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y transactions / sec"
                }
            };
        },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesTransactionsPerSecond"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotTransactionsPerSecond"), dataset, options);
        // setup overview
        $.plot($("#overviewTransactionsPerSecond"), dataset, prepareOverviewOptions(options));
    }
};

// Transactions per second
function refreshTransactionsPerSecond(fixTimestamps) {
    var infos = transactionsPerSecondInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyTransactionsPerSecond");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotTransactionsPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTransactionsPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTransactionsPerSecond", "#overviewTransactionsPerSecond");
        $('#footerTransactionsPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var totalTPSInfos = {
        data: {"result": {"minY": 98.0, "minX": 1.763685241E12, "maxY": 201.0, "series": [{"data": [[1.763685245E12, 167.0], [1.763685244E12, 166.0], [1.763685243E12, 167.0], [1.763685248E12, 166.0], [1.763685247E12, 168.0], [1.763685246E12, 166.0], [1.76368525E12, 167.0], [1.763685249E12, 166.0], [1.763685242E12, 168.0], [1.763685241E12, 201.0], [1.763685251E12, 98.0]], "isOverall": false, "label": "Transaction-success", "isController": false}, {"data": [], "isOverall": false, "label": "Transaction-failure", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.763685251E12, "title": "Total Transactions Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of transactions / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendTotalTPS"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y transactions / sec"
                },
                colors: ["#9ACD32", "#FF6347"]
            };
        },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesTotalTPS"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotTotalTPS"), dataset, options);
        // setup overview
        $.plot($("#overviewTotalTPS"), dataset, prepareOverviewOptions(options));
    }
};

// Total Transactions per second
function refreshTotalTPS(fixTimestamps) {
    var infos = totalTPSInfos;
    // We want to ignore seriesFilter
    prepareSeries(infos.data, false, true);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotTotalTPS"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTotalTPS");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTotalTPS", "#overviewTotalTPS");
        $('#footerTotalTPS .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

// Collapse the graph matching the specified DOM element depending the collapsed
// status
function collapse(elem, collapsed){
    if(collapsed){
        $(elem).parent().find(".fa-chevron-up").removeClass("fa-chevron-up").addClass("fa-chevron-down");
    } else {
        $(elem).parent().find(".fa-chevron-down").removeClass("fa-chevron-down").addClass("fa-chevron-up");
        if (elem.id == "bodyBytesThroughputOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshBytesThroughputOverTime(true);
            }
            document.location.href="#bytesThroughputOverTime";
        } else if (elem.id == "bodyLatenciesOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshLatenciesOverTime(true);
            }
            document.location.href="#latenciesOverTime";
        } else if (elem.id == "bodyCustomGraph") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshCustomGraph(true);
            }
            document.location.href="#responseCustomGraph";
        } else if (elem.id == "bodyConnectTimeOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshConnectTimeOverTime(true);
            }
            document.location.href="#connectTimeOverTime";
        } else if (elem.id == "bodyResponseTimePercentilesOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimePercentilesOverTime(true);
            }
            document.location.href="#responseTimePercentilesOverTime";
        } else if (elem.id == "bodyResponseTimeDistribution") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimeDistribution();
            }
            document.location.href="#responseTimeDistribution" ;
        } else if (elem.id == "bodySyntheticResponseTimeDistribution") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshSyntheticResponseTimeDistribution();
            }
            document.location.href="#syntheticResponseTimeDistribution" ;
        } else if (elem.id == "bodyActiveThreadsOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshActiveThreadsOverTime(true);
            }
            document.location.href="#activeThreadsOverTime";
        } else if (elem.id == "bodyTimeVsThreads") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTimeVsThreads();
            }
            document.location.href="#timeVsThreads" ;
        } else if (elem.id == "bodyCodesPerSecond") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshCodesPerSecond(true);
            }
            document.location.href="#codesPerSecond";
        } else if (elem.id == "bodyTransactionsPerSecond") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTransactionsPerSecond(true);
            }
            document.location.href="#transactionsPerSecond";
        } else if (elem.id == "bodyTotalTPS") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTotalTPS(true);
            }
            document.location.href="#totalTPS";
        } else if (elem.id == "bodyResponseTimeVsRequest") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimeVsRequest();
            }
            document.location.href="#responseTimeVsRequest";
        } else if (elem.id == "bodyLatenciesVsRequest") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshLatenciesVsRequest();
            }
            document.location.href="#latencyVsRequest";
        }
    }
}

/*
 * Activates or deactivates all series of the specified graph (represented by id parameter)
 * depending on checked argument.
 */
function toggleAll(id, checked){
    var placeholder = document.getElementById(id);

    var cases = $(placeholder).find(':checkbox');
    cases.prop('checked', checked);
    $(cases).parent().children().children().toggleClass("legend-disabled", !checked);

    var choiceContainer;
    if ( id == "choicesBytesThroughputOverTime"){
        choiceContainer = $("#choicesBytesThroughputOverTime");
        refreshBytesThroughputOverTime(false);
    } else if(id == "choicesResponseTimesOverTime"){
        choiceContainer = $("#choicesResponseTimesOverTime");
        refreshResponseTimeOverTime(false);
    }else if(id == "choicesResponseCustomGraph"){
        choiceContainer = $("#choicesResponseCustomGraph");
        refreshCustomGraph(false);
    } else if ( id == "choicesLatenciesOverTime"){
        choiceContainer = $("#choicesLatenciesOverTime");
        refreshLatenciesOverTime(false);
    } else if ( id == "choicesConnectTimeOverTime"){
        choiceContainer = $("#choicesConnectTimeOverTime");
        refreshConnectTimeOverTime(false);
    } else if ( id == "choicesResponseTimePercentilesOverTime"){
        choiceContainer = $("#choicesResponseTimePercentilesOverTime");
        refreshResponseTimePercentilesOverTime(false);
    } else if ( id == "choicesResponseTimePercentiles"){
        choiceContainer = $("#choicesResponseTimePercentiles");
        refreshResponseTimePercentiles();
    } else if(id == "choicesActiveThreadsOverTime"){
        choiceContainer = $("#choicesActiveThreadsOverTime");
        refreshActiveThreadsOverTime(false);
    } else if ( id == "choicesTimeVsThreads"){
        choiceContainer = $("#choicesTimeVsThreads");
        refreshTimeVsThreads();
    } else if ( id == "choicesSyntheticResponseTimeDistribution"){
        choiceContainer = $("#choicesSyntheticResponseTimeDistribution");
        refreshSyntheticResponseTimeDistribution();
    } else if ( id == "choicesResponseTimeDistribution"){
        choiceContainer = $("#choicesResponseTimeDistribution");
        refreshResponseTimeDistribution();
    } else if ( id == "choicesHitsPerSecond"){
        choiceContainer = $("#choicesHitsPerSecond");
        refreshHitsPerSecond(false);
    } else if(id == "choicesCodesPerSecond"){
        choiceContainer = $("#choicesCodesPerSecond");
        refreshCodesPerSecond(false);
    } else if ( id == "choicesTransactionsPerSecond"){
        choiceContainer = $("#choicesTransactionsPerSecond");
        refreshTransactionsPerSecond(false);
    } else if ( id == "choicesTotalTPS"){
        choiceContainer = $("#choicesTotalTPS");
        refreshTotalTPS(false);
    } else if ( id == "choicesResponseTimeVsRequest"){
        choiceContainer = $("#choicesResponseTimeVsRequest");
        refreshResponseTimeVsRequest();
    } else if ( id == "choicesLatencyVsRequest"){
        choiceContainer = $("#choicesLatencyVsRequest");
        refreshLatenciesVsRequest();
    }
    var color = checked ? "black" : "#818181";
    if(choiceContainer != null) {
        choiceContainer.find("label").each(function(){
            this.style.color = color;
        });
    }
}


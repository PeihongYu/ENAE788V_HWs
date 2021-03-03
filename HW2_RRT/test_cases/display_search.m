% Copyright 2018, Michael Otte
%
% Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
%
%The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
%
%THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
%
% this will display the search tree and path
% assuming that the files have been generated

close all;

id = 5;
goalRegions = [-38 20 10; -48 20 10; -45 45 15; 18 -45 5; 38 -8 3];
goal = goalRegions(id, :);

obstacles = csvread('obstacles.txt');
search_tree_raw = csvread(['search_tree_', int2str(id), '.txt']);
path_raw = csvread(['output_path_', int2str(id), '.txt']);

search_tree = nan(3*size(search_tree_raw, 1), 2);

search_tree(1:3:end-2, 1) = search_tree_raw(:, 2);
search_tree(2:3:end-1, 1) = search_tree_raw(:, 5);
search_tree(1:3:end-2, 2) = search_tree_raw(:, 3);
search_tree(2:3:end-1, 2) = search_tree_raw(:, 6);

figure
viscircles(goal(1:2),goal(3),'Color','b');
for i = 1:20
    viscircles(obstacles(i, 1:2),obstacles(i, 3));
    hold on;
end
plot(search_tree(:, 1), search_tree(:, 2), 'm', 'LineWidth', 2);
hold on
plot(path_raw(end,2) , path_raw(end,3), 'xb', 'markersize', 10, 'linewidth', 2)
hold on
plot(path_raw(:,2), path_raw(:,3), 'g:', 'LineWidth', 3);
axis equal
grid on
hold off

saveas(gcf, [int2str(id), '.png'])
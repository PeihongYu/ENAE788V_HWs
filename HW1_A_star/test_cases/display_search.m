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

% Algorithms: Dijkstra, A_star
ALGORITHM = 'A_star';

start_ids = [9, 88, 30, 38, 38];
end_ids = [5, 9, 95, 502, 5002];

id = 1;
search_tree_raw = csvread(['search_tree_', int2str(id), '_', ALGORITHM, '.txt']);
path_raw = csvread(['output_path_', int2str(id), '_', ALGORITHM, '.txt']);
nodes_raw = csvread(['nodes_', int2str(id), '.txt']);
edges_raw = csvread(['edges_with_costs_', int2str(id)', '.txt']);

startNodeID = start_ids(id);
goalNodeID = end_ids(id);

% a bit of data processing for faster plotting
search_tree = nan(3*size(search_tree_raw, 1), 2);

search_tree(1:3:end-2, 1) = search_tree_raw(:, 2);
search_tree(2:3:end-1, 1) = search_tree_raw(:, 5);
search_tree(1:3:end-2, 2) = search_tree_raw(:, 3);
search_tree(2:3:end-1, 2) = search_tree_raw(:, 6);

nodes = nodes_raw(2:end,2:3);

edges_raw = edges_raw(2:end,:);

edges = nan(3*size(edges_raw, 1), 2);

edges(1:3:end-2, 1) = nodes(edges_raw(:, 1),1);
edges(2:3:end-1, 1) = nodes(edges_raw(:, 2),1);
edges(1:3:end-2, 2) = nodes(edges_raw(:, 1),2);
edges(2:3:end-1, 2) = nodes(edges_raw(:, 2),2);

figure(2)
plot(nodes(:,1), nodes(:,2), 'ok')
hold on
% for i = 1:length(nodes)
%     text(nodes(i, 1)+0.5, nodes(i, 2), int2str(i-1), 'FontSize', 20)
%     hold on;
% end
plot(nodes(startNodeID,1) , nodes(startNodeID,2), 'or', 'markersize', 10, 'linewidth', 2)
hold on
plot(nodes(goalNodeID,1) , nodes(goalNodeID,2), 'xr', 'markersize', 10, 'linewidth', 2)
hold on
plot(edges(:,1), edges(:,2), 'k')
hold on
plot(search_tree(:, 1), search_tree(:, 2), 'm', 'LineWidth', 2);
plot(path_raw(:,2), path_raw(:,3), 'g:', 'LineWidth', 3);
axis equal
hold off

% saveas(gcf, [int2str(id), '_', ALGORITHM, '.png'])